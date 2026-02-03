export const getPosts = async (queryParams) => {
  try {
    const url = new URL('posts', import.meta.env.VITE_BACKEND_URL)

    Object.entries(queryParams).forEach(([k, v]) => {
      if (v !== undefined && v !== null && v !== '') url.searchParams.set(k, v)
    })

    const res = await fetch(url.toString())
    return await res.json()
  } catch (err) {
    console.error('error fetching posts:', err)
  }
}

export const createPost = async (post) => {
  try {
    const url = new URL('posts', import.meta.env.VITE_BACKEND_URL)
    const res = await fetch(url.toString(), {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(post),
    })
    return await res.json()
  } catch (err) {
    console.error('error creating post:', err)
  }
}
