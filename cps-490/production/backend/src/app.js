import express from 'express'
import { userRoutes } from './routes/users.js'
import bodyParser from 'body-parser'
import { createServer } from 'node:http'
import { Server } from 'socket.io'
import { handleSocket } from './socket.js'
import path from 'path'
import { fileURLToPath } from 'url'

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

const app = express()
app.use(bodyParser.json())

app.use((req, res, next) => {
  res.header('Access-Control-Allow-Origin', 'http://localhost:5173')
  res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS')
  res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization')

  if (req.method === 'OPTIONS') {
    return res.status(200).end()
  }

  next()
})

userRoutes(app)

const clientDist = path.resolve(__dirname, "../..", "frontend", "dist")
app.use(express.static(clientDist))

app.get('*', (req, res) => {
  res.sendFile(path.join(clientDist, "index.html"))
})

const server = createServer(app)
const io = new Server(server, {
  cors: {
    origin: '*',
  },
})
handleSocket(io)

export { server as app }
