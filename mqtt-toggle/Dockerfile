# Use Node.js as base image
FROM node:18

# Create app directory
WORKDIR /app

# Copy dependency files
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the app code
COPY . .

# Expose the port used by the app
EXPOSE 1880

# Start the app
CMD ["node", "mqtt_pub.js"]
