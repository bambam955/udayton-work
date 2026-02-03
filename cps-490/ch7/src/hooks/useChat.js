import { useState, useEffect } from 'react'
import { useSocket } from '../contexts/SocketIOContext'

export function useChat() {
  const { socket } = useSocket()
  const [messages, setMessages] = useState([])
  function receiveMessage(message) {
    setMessages((messages) => [...messages, message])
  }
  useEffect(() => {
    socket.on('chat.message', receiveMessage)
    return () => socket.off('chat.message', receiveMessage)
  }, [])
  function sendMessage(message) {
    socket.emit('chat.message', message)
  }
  return { messages, sendMessage }
}
