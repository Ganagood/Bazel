#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
PROJECT_DIR="${ROOT_DIR}/demo-project"
IMAGE_NAME="${IMAGE_NAME:-bazel-demo-practice}"
CONTAINER_NAME="${1:-bazel-demo-practice}"

if ! command -v docker >/dev/null 2>&1; then
  echo "docker is required to start the practice container." >&2
  exit 1
fi

if ! docker info >/dev/null 2>&1; then
  echo "Docker daemon is not running. Start Docker Desktop and retry." >&2
  exit 1
fi

echo "Building ${IMAGE_NAME} from ${PROJECT_DIR}..."
docker build -t "${IMAGE_NAME}" "${PROJECT_DIR}"

echo "Starting ${CONTAINER_NAME}. Your demo project will be mounted at /workspace."
docker run --rm -it \
  --name "${CONTAINER_NAME}" \
  -v "${PROJECT_DIR}:/workspace" \
  -w /workspace \
  "${IMAGE_NAME}"
