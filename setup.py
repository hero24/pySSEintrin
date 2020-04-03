from distutils.core import setup, Extension

def main():
    setup(name="pysseintrin",
          version="1.0.0",
          description="SSE wrapper for Python",
          author="hero24",
          packages=["pysseintrin"],
          ext_modules=[Extension("pysseintrin", ["pysseintrin/sseintrin/sseintrin.c"]),
                       Extension("mxcsrctrl", ["pysseintrin/mxcsrctrl/mxcsrctrl.c"])])

if __name__ == "__main__":
    main()

