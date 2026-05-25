import { defineConfig } from 'vite'
import { fileURLToPath } from 'node:url'
import tailwindcss from '@tailwindcss/vite'

export default defineConfig({
  base: '/',
  plugins: [
    tailwindcss(),
  ],
  build: {
    rollupOptions: {
      // Explicitly list each HTML page we want emitted during production builds.
      // Without this, Vite treats the app as single-page and only builds index.html.
      input: {
        index: fileURLToPath(new URL('./index.html', import.meta.url)),
        lab4: fileURLToPath(new URL('./lab4.html', import.meta.url)),
        // Use a nested entry name so Vite emits dist/webchatclient/index.html.
        'webchatclient/index': fileURLToPath(new URL('./webchatclient/index.html', import.meta.url)),
      },
    },
  },
})
