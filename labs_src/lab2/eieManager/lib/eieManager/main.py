import uvicorn


def main():
    uvicorn.run("eieManager.APIServer.main:app")


if __name__ == "__main__":
    main()
