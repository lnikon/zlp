FROM alpine:latest

RUN apk add --no-cache cmake gcc make

WORKDIR /app

COPY . /app

