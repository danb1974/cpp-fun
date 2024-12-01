# Base image with OpenCV
FROM ubuntu:22.04

# Avoid prompts
ENV DEBIAN_FRONTEND noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    libopencv-dev \
    # libgtk-3-dev \
    && apt-get clean

# Set DISPLAY for X11 forwarding
#ENV DISPLAY=${DISPLAY}
ENV DISPLAY=:0

# Set the working directory
WORKDIR /workspace
