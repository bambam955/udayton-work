import { Message } from '../db/models/messages.js'

export async function createMessage({ username, message, room }) {
  const messageDoc = new Message({ username, message, room })
  return await messageDoc.save()
}

export async function getMessagesByRoom(room) {
  return (await Message.find({ room })).toSorted((a, b) => a.sent - b.sent)
}
