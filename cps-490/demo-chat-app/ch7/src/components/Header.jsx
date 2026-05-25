import { Link } from 'react-router-dom'
import { useAuth } from '../contexts/AuthContext.jsx'
import { jwtDecode } from 'jwt-decode'
import { User } from './User.jsx'
import { useSocket } from '../contexts/SocketIOContext.jsx'

export function Header() {
  const [token, setToken] = useAuth()
  const { socket } = useSocket()
  const handleLogout = () => {
    socket.disconnect()
    setToken(null)
  }
  if (token) {
    const { sub } = jwtDecode(token)
    return (
      <div>
        Logged in as <User id={sub} />
        <br />
        <button onClick={handleLogout}>Logout</button>
      </div>
    )
  }
  return (
    <div>
      <Link to='/login'>Login</Link> | <Link to='/signup'>Sign Up</Link>
    </div>
  )
}
