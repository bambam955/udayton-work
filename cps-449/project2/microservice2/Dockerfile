FROM dhi.io/node:22-alpine3.23-dev

WORKDIR /app

# Install deps
COPY package*.json ./
RUN npm ci --no-audit --no-fund

# Copy app source
COPY . .

EXPOSE 8080

CMD ["npm", "start"]
