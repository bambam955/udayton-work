# cps449-microservice2

Codebase for the second microservice in CPS 449.

## Chat proxy

`microservice2` exposes:
- `POST /chat` with a body shaped as `{ "message": ... }`
- `POST /chat/reset`

The service keeps OpenRouter API key and model configuration server-side so the frontend never sees secrets.

## Environment variables

Use `.env` (or platform environment variables) for these values.

- `OPENROUTER_API_KEY` (required)
- `OPENROUTER_MODEL` (default: `openrouter/free`)
- `OPENROUTER_URL` (optional)
- `CHAT_SESSION_TTL_MS` (optional)
- `CHAT_SESSION_MAX_MESSAGES` (optional)
- `CHAT_CLEANUP_INTERVAL_MS` (optional)
- `CHAT_REQUEST_TIMEOUT_MS` (optional)

Copy values from `.env.example` into `.env` for local development, then set in your runtime environment for deployment.

## Local container run

The container image copies `.env` during build and `index.js` loads it at startup (if present), so you can run locally without passing `--env-file`:

```bash
docker run --rm -it -p 8080:8080 bambam955/cps449:microservice2
```

If you deploy from your host environment or cloud service, set `OPENROUTER_API_KEY` as a runtime secret instead of baking it into the image.
