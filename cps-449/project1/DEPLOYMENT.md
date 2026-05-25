# Deployment Steps (Azure VM)

## Base Path Note

This project is configured with `base: '/profile/'` in `vite.config.ts`.
That means production hosting must serve the app from `/profile/` (not from domain root).

## 1. Build locally on the VM

Run these commands from the `project1` folder:

```bash
npm ci
npm run build
```

This creates production files in `dist/`.

## 2. Copy build output to Apache folder

```bash
sudo mkdir -p /var/www/html/profile
sudo cp -r dist/* /var/www/html/profile/
```

The page will be available at:

> http://cps449-mooreb26.canadacentral.cloudapp.azure.com/profile/

## 3. Verify runtime behavior on the deployed URL

Check these in the browser:

- Digital and analog clocks update continuously
- Email show/hide toggle works
- Skills filter works
- Joke API auto-refreshes every 30 seconds
- XKCD image loads
- AI chat works using configured `VITE_OPENROUTER_API_KEY`

## 4. Update workflow for future edits

For each update, run this in the Azure VM:

```bash
npm run build
sudo cp -r dist/* /var/www/html/profile/
```
