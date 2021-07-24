from distutils.core import setup, Extension

def main():
    setup(name="tachnet",
          version="1.0.0",
          description="Astronomically fast deep learning library",
          author="Nitin Narayanan",
          author_email="nitinnarayanan77@gmail.com",
          ext_modules=[Extension("tachnet", ["fastsqr.c"])])

if __name__ == "__main__":
    main()