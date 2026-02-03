import { ChatRoom } from '../components/ChatRoom'
import { Header } from '../components/Header'
import { Status } from '../components/Status'
import { useSocket } from '../contexts/SocketIOContext'

export function Chat() {
  const { status } = useSocket()
  return (
    <div style={{ padding: 8 }}>
      <Header />
      <br />
      <hr />
      <br />
      <Status />
      <br />
      <hr />
      <br />
      {status === 'connected' && <ChatRoom />}
    </div>
  )
}
