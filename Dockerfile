FROM gcc:latest as build

RUN apt-get update && \
    apt-get install -y \
      build-essential \
      cmake \

# ADD ./compilation /app
# ADD ./apps /app

# WORKDIR /app/build

# RUN cmake ..
# RUN cmake --build .

# FROM ubuntu:latest

# RUN groupadd -r sample && useradd -r -g sample sample
# USER sample

# WORKDIR /app

# COPY --from=build /app/build/apps/main_driver/src/main_driver .

# ENTRYPOINT ["./main_driver"]

