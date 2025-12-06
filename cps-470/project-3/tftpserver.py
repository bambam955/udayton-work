"""
- CPS470
- Spring 2025
- Team: 
- Names:
  - Jeremy Sowder
  - Bennett Moore

A Trivial File Transfer Protocol Server
"""

import socket
import os
import math
import struct
import datetime
import sys

# Helpful constants used by TFTP
TFTP_PORT = 69
TFTP_BLOCK_SIZE = 512
MAX_UDP_PACKET_SIZE = 65535 # from 1 to 65535

def main():
    """
    Processes a single TFTP request
    """

    # Verify platform is supported before proceeding.
    if sys.platform not in ('win32', 'linux'):
        raise Exception('Unsupported platform')

    client_socket = socket_setup()
    fd = -1 # Use one file descriptor to open the file for sending
    start_time = None
    print("Server is ready to receive a request")

    try:
        # Wait for incoming TFTP request from client.
        client_raw_req, client_addr = client_socket.recvfrom(MAX_UDP_PACKET_SIZE)
        (filename, mode) = parse_conn_msg(client_raw_req)
        
        # Validate that the requested file exists on the server.
        # Error out immediately if not.
        full_filepath = 'server/' + filename # Place all files in server/ subdir
        print(f'Requested file: {filename}')
        if not os.path.exists(full_filepath):
            client_socket.sendto(create_error_msg(1), client_addr) # Let client know there was a problem
            raise Exception(f'file \"{filename}\" could not be found.')
        
        # Open file and prepare to send data blocks.
        print(f'Transfer mode: {mode}')
        num_blocks = get_file_block_count(full_filepath)
        if sys.platform == 'win32':
            # Windows needs this special O_BINARY flag for opening files.
            fd = os.open(full_filepath, os.O_RDONLY | os.O_BINARY)
        else:
            # Linux opens files as binary by default. No need for an extra flag.
            fd = os.open(full_filepath, os.O_RDONLY)
        i = 1
        print(f'Sending file {filename} to host {client_addr}...')
        start_time = datetime.datetime.now()
        print(f'Started sending file at {start_time}')
        
        # Send each block of the file and wait for acknowledgement.
        # TFTP is a stop-and-wait protocol.
        while i <= num_blocks:
            next_block_num = i % 65536 # Wrap around block number if needed
            next_block = get_file_block(fd, i) # Uses already opened fd
            next_msg = create_data_msg(next_block_num, next_block)
            client_socket.sendto(next_msg, client_addr)
            # Output formatted such that it all stays on one line.
            print(f'\rPacket {i} (block num {next_block_num}) sent...', end='')

            # Receive and process client response.
            client_raw_ret, _ = client_socket.recvfrom(MAX_UDP_PACKET_SIZE)
            ret_op_code = struct.unpack('!H', client_raw_ret[:2])[0]
            if ret_op_code == 4:
                # Received an ACK...verify that it acknowledged the correct block.
                # Increment the counter to move to the next block only if the current one was ACKed.
                acked_block_num = parse_ack_msg(client_raw_ret)
                if acked_block_num == next_block_num:
                    print(f'packet {acked_block_num} ACKed by client.', end='')
                    i += 1
                elif acked_block_num == (next_block_num - 1) % 65536:
                    # Duplicate ACK for previous block...resend the current block.
                    # Note that this happens automatically because the counter doesn't increment,
                    # but it's good to debug what's going on.
                    print(f'Duplicate ACK for packet {acked_block_num}. Resending block {i}', end='')
            elif ret_op_code == 5:
                # Error received from client.
                (_, err_msg) = parse_err_msg(client_raw_ret)
                raise Exception(err_msg)
            else:
                # No other op-codes should be sent...
                raise Exception(f'Invalid ACK op-code {ret_op_code}')
                    
    except Exception as e:
        print(f'Error: {e}')

    # Clean everything up, then close the connection.
    print('')
    if start_time is not None:
        end_time = datetime.datetime.now()
        time_elapsed = end_time - start_time
        print(f'Finished sending file at {end_time}. Elapsed: {time_elapsed.seconds} seconds.')
    if fd != -1:
        os.close(fd)
    client_socket.close()

def get_file_block_count(filename: str) -> int:
    """
    Determines the number of TFTP blocks for the given file
    :param filename: The name of the file
    :return: The number of TFTP blocks for the file or -1 if the file does not exist
    """
    try:
        # This will throw an exception if the file doesn't exist.
        file_size = os.stat(filename).st_size
        return math.ceil(file_size / TFTP_BLOCK_SIZE)
    except:
        return -1

def get_file_block(fd: int, block_number: int) -> bytes:
    """
    Get the file block data for the given file and block number
    :param fd: The file descriptor of the file to read
    :param block_number: The block number (1 based)
    :return: The data contents (as a bytes object) of the file block
    """
    block_byte_offset = (block_number-1) * TFTP_BLOCK_SIZE
    os.lseek(fd, block_byte_offset, os.SEEK_SET)
    block_data = os.read(fd, TFTP_BLOCK_SIZE)
    return block_data

def socket_setup() -> socket.socket:
    """
    Sets up a UDP socket to listen on the TFTP port
    :return: The created socket
    """
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(('', TFTP_PORT))
    # If there is no activity for 5 minutes then the server exits.
    s.settimeout(5 * 60)
    return s

def parse_conn_msg(packet: bytes) -> tuple[str, str]:
    """
    Parse the initial TFTP request message from client
    """
    # Extract op-code (first 2 bytes, big-endian).
    (op_code,) = struct.unpack("!H", packet[:2])

    # Only accept read requests (op-code 1), not write requests.
    if op_code != 1:
        raise ValueError('only RRQs are accepted')

    # Parse null-terminated strings for filename and transfer mode.
    fields = packet[2:].split(b'\x00')
    filename = fields[0].decode()
    mode = fields[1].decode()

    # Validate that the parsed mode is supported.
    valid_modes = ['netascii', 'octet']
    if mode not in valid_modes:
        raise ValueError(f'invalid mode {mode}')

    return (filename, mode)

def parse_ack_msg(packet: bytes) -> int:
    """
    Parse acknowledgement message from client (op-code 4)
    """
    (opcode, block_num) = struct.unpack('!HH', packet[:4])
    if opcode != 4:
        raise ValueError('Unexpected op-code in ACK message')
    
    return block_num

def parse_err_msg(packet: bytes) -> tuple[int, str]:
    """
    Parse error message from client (op-code 5)
    """
    (opcode, err_code) = struct.unpack('!HH', packet[:4])
    if opcode != 5:
        raise ValueError('Unexpected op-code in error message')
    
    err_msg = packet[4:].decode('ascii')
    return (err_code, err_msg)

def create_data_msg(block_num: int, data: bytes) -> bytes:
    """
    Create a TFTP data message (op-code 3) containing a file block
    """
    op_code = 3
    msg = struct.pack('!HH', op_code, block_num) + data
    return msg

def create_error_msg(error_code: int) -> bytes:
    """
    Create a TFTP error message (op-code 5) with standard TFTP error codes
    """
    if error_code < 0 or error_code > 7:
        raise ValueError('Error code must be a value between 0 and 7')
    error_msg_options = ['Not defined, see error message', 'File not found', 'Access violation', 'Disk full or allocation exceeded',
            'Illegal TFTP operation', 'Unknown transfer ID', 'File already exists', 'No such user']
    error_msg: str = error_msg_options[error_code]
    op_code = 5
    
    msg = struct.pack("!HH", op_code, error_code) + error_msg.encode()
    return msg

main()
