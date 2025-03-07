import argparse


INCLUDE   = "#include"
DEFINE    = "#define"
TYPEDEF   = "typedef"
STRUCT    = "struct"

T_PREFIX  = "__int_" 

ARG_BEGIN = "// arg-begin"
ARG_END   = "// arg-end"


def main() -> None:
    arg_parser = argparse.ArgumentParser(
        description='A program which converts a C code with pre-defined syntax into a C macro, which can be used to quickly generate data structures.'
    )
    
    arg_parser.add_argument(
        'source',
        type=str,
        help='The source C file'
    )
    
    args = arg_parser.parse_args()
    
    source : str = args.source
    destination = source.replace('int_', '')
    
    try:
        with open(source, 'r') as file:
            lines = file.readlines()
    except FileNotFoundError:
        print(f"Error: Source file {source} not found.")
    except Exception as e:
        print(f"An error occurred: {e}")
        
        
    try:
        outfile = open(destination, 'w')
    except FileNotFoundError:
        print(f"Error: Source file {source} not found.")
    except Exception as e:
        print(f"An error occurred: {e}")
        
    
    header_name = destination.split('/')[-1].split(".")[0].upper()

    outfile.write(f"#ifndef {header_name}\n")
    outfile.write(f"#define {header_name}\n")
    
    ignore = False
    
    for line in lines:
        if line.startswith(ARG_END):
            ignore = False
            
            macro = ""
            macro += f"#define GENERATE_{header_name.upper()}(type) \\\n"
            
            outfile.write(macro)

            continue
            
        if line.startswith(ARG_BEGIN):
            ignore = True
            continue
        
        if ignore:
            continue
        
        # if it begins with #include, copy it as it is
        if line.startswith(INCLUDE):
            outfile.write(line)
            continue
            
        # if it is a predefined macro, copt it as it is
        if line.startswith(DEFINE):
            outfile.write(line)
            continue
                            
        # otherwise follow the predefined syntax to replace all `__int` with `type##`
        macro = ""
        
        if line == "\n":
            macro += "\\\n"
        else:    
            macro += f"{line.replace('__int ', 'type ').replace('__int_', 'type##_').rstrip().replace('__int', 'type')} \\\n"
            
        outfile.write(macro)
                        
    outfile.write("\n")
    outfile.write(f"#endif // {header_name}\n")
    
    outfile.close()
                    

if __name__ == '__main__':
    main()
    