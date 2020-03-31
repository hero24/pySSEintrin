from distutils.core import setup, Extension

def main():
    setup(name="pysseintrin",
          version="1.0.0",
          description="SSE wrapper for Python",
          author="hero24",
          ext_modules=[Extension("pysseintrin", ["pysseintrin.c"])])

if __name__ == "__main__":
    main()

