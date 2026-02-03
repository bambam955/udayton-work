import { useChat } from '../hooks/useChat'
import { ChatMessage } from './ChatMessage'
import { EnterMessage } from './EnterMessage'

export function ChatRoom() {
  const { messages, sendMessage } = useChat()
  return (
    <div>
      {messages.map((message, index) => (
        <ChatMessage key={index} {...message} />
      ))}
      <EnterMessage onSend={sendMessage} />
    </div>
  )
}
