from typing import List
import logging
import os

import argparse

logging.basicConfig(level=logging.INFO)

# Constants
INCLUDE   : str = '#include'
DEFINE    : str = '#define'
TYPEDEF   : str = 'typedef'
STRUCT    : str = 'struct'

T_PREFIX  : str = '__t_' 

ARG_BEGIN : str = '// arg-begin'
ARG_END   : str = '// arg-end'


class Pipe():
    '''Custom Pipe class to pipe functions.
    
    Example:
    ```
    def foo(i):
        ...
    
    def bar(i):
        ...
        
    a = Pipe(10) | foo | bar
    a = a.unwrap()  # a = bar(foo(10))
    ```
    '''
    def __init__(self, value):
        self.value = value
    
    def __or__(self, func):
        return Pipe(func(self.value))
    
    def unwrap(self):
        return self.value


def reduce_filename(file_name : str) -> str:
    '''Reduces the filename by removing __t_ prefix.'''
    
    return file_name.replace(T_PREFIX, '')


def get_filename(file_path : str) -> str:
    '''Get the filename from a filepath. Preserves file extension.'''
    
    return file_path.split('/')[-1]


def get_base_filename(file_name : str) -> str:
    '''Remove the extension from the filename, hence returning the base filename.'''
    
    return file_name.split('.')[0]


def get_header_name(file_path : str) -> str:
    p = Pipe(file_path) | get_filename | get_base_filename | reduce_filename | str.upper
    return p.unwrap()


def read_lines(file_path : str) -> List[str]:
    try:
        with open(file_path, 'r+') as file:
            return file.readlines()
        
    except FileNotFoundError:
        logging.error(f'Error: File {file_path} not found.')
        exit(1)
        
    except Exception as e:
        logging.error(f'An error occurred: {e}')
        exit(1)


def open_outfile(file_path : str):
    try:
        os.makedirs(os.path.dirname(file_path), exist_ok=True)
        
        return open(file_path, 'w')
        
    except FileNotFoundError:
        logging.error(f'Error: Source file {file_path} not found.')
        exit(1)
        
    except Exception as e:
        logging.error(f'An error occurred: {e}')
        exit(1)


def convert_generic(outfile, lines : List[str], header_name : str) -> None:
    ignore = False
    
    outfile.write(f'#ifndef {header_name}\n')
    outfile.write(f'#define {header_name}\n')
    
    for line in lines:
        if line.startswith(ARG_END):
            ignore = False
            
            macro = ''
            macro += f'#define GENERATE_{header_name.upper()}(type) \\\n'
            
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
        macro = ''
        
        if line == '\n':
            macro += '\\\n'
        else:    
            macro += f"{line.replace('__t ', 'type ').replace('__t_', 'type##_').rstrip().replace('__t', 'type')} \\\n"
            
        outfile.write(macro)
                        
    outfile.write('\n')
    outfile.write(f'#endif // {header_name}\n')


def convert_void(outfile, lines : List[str]) -> None:
    ignore = False
    
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
        macro = ''
        
        if line == '\n':
            macro += line
        else:    
            macro += f"{line.replace('__t_', '').replace('__t', 'void *').rstrip().replace('__t', 'type')} \n"
            
        outfile.write(macro)
                        
    outfile.write('\n')


def make_arg_parser():
    '''A function to return an argument parser for CLI.'''
    
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
    
    return arg_parser.parse_args()


def main() -> None:
    args = make_arg_parser()
    
    source      : str = args.source
    destination : str = args.output
    type        : str = args.type
    
    if type not in ['void', 'generic']:
        logging.error(f'Invalid type: {type}')
        exit(1)
    
    lines       : List[str] = read_lines(source)
    outfile                 = open_outfile(destination)
    header_name : str       = get_header_name(source)

    
    if type == 'generic':
        convert_generic(outfile, lines, header_name)
    elif type == 'void':
        convert_void(outfile, lines)
    
    outfile.close()

if __name__ == '__main__':
    main()
