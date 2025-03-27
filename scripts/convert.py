import argparse


INCLUDE   : str = "#include"
DEFINE    : str = "#define"
TYPEDEF   : str = "typedef"
STRUCT    : str = "struct"

T_PREFIX  : str = "__t_" 

ARG_BEGIN : str = "// arg-begin"
ARG_END   : str = "// arg-end"


def main() -> None:
    arg_parser = argparse.ArgumentParser(
        prog='Converter',
        description='A program which converts a C code with pre-defined syntax into a C macro, which can be used to quickly generate data structures.'
    )
    
    arg_parser.add_argument(
        '-s', '--source',
        type=str,
        help='The source C file'
    )
    
    arg_parser.add_argument(
        '-o', '--output',
        type=str,
        help='The output file'
    )
    
    arg_parser.add_argument(
        '-t', '--type',
        type=str,
        help='Type of conversion: void OR generic'
    )
    
    args = arg_parser.parse_args()
    
    source      : str = args.source
    destination : str = args.output
    type        : str = args.type
    
    if type != 'void' and type != 'generic':
        print(f'Invalid type: {type}')
        exit(1)
    
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
        
    
    header_name = source.replace('__t_', '').split('/')[-1].split(".")[0].upper()

    ignore = False
    
    if type == 'generic':
        outfile.write(f"#ifndef {header_name}\n")
        outfile.write(f"#define {header_name}\n")
        
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
                                
            # otherwise follow the predefined syntax to replace all `__t` with `type##`
            macro = ""
            
            if line == "\n":
                macro += "\\\n"
            else:    
                macro += f"{line.replace('__t ', 'type ').replace('__t_', 'type##_').rstrip().replace('__t', 'type')} \\\n"
                
            outfile.write(macro)
                            
        outfile.write("\n")
        outfile.write(f"#endif // {header_name}\n")
        
    elif type == 'void':
        for line in lines:
            if line.startswith(ARG_END):
                ignore = False                
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
            
            # otherwise follow the predefined syntax to replace all `__t_` with `` and `__t` with `void *`
            macro = ""
            
            if line == "\n":
                macro += line
            else:    
                macro += f"{line.replace('__t_', '').replace('__t', 'void *').rstrip().replace('__t', 'type')} \n"
                
            outfile.write(macro)
                            
        outfile.write("\n")

    
    outfile.close()
                    

if __name__ == '__main__':
    main()
    