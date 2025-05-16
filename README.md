# dataConverter
---
Convert the data stored in CSV to a bin file to reduce the size of the data file




### Usage

Build: ```make```

Usage: 
```
./dcver.exe [options]

Options:

    -h, --help             Show this help message

    -v, --version          Show the version

    -i, --input <file>     Specify input file

    -o, --output <file>    Specify output file

    -m, --mode <mode>      Specify data mode (bin, char, int, float). Default is float.

```

### Example
./dcver -i data.csv -o data.bin -m float
