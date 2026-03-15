# a python script to convert .png sprites into
# .h files usable by tiny_graphics
# vibe coded because i dont like python :p

import sys
import os
from PIL import Image

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py input.png")
        sys.exit(1)
    
    input_file = sys.argv[1]
    if not input_file.lower().endswith('.png'):
        print("Input file must be a .png file.")
        sys.exit(1)
    
    try:
        im = Image.open(input_file)
        im = im.convert('RGBA')  # Convert to RGBA to handle alpha uniformly
        width, height = im.size
        
        # Check if all pixels are black or white (ignoring alpha if fully opaque)
        for y in range(height):
            for x in range(width):
                r, g, b, a = im.getpixel((x, y))
                if a != 255:
                    print("Image contains transparent pixels, which is not allowed.")
                    sys.exit(1)
                if not ((r, g, b) == (0, 0, 0) or (r, g, b) == (255, 255, 255)):
                    print("Image is not strictly black and white.")
                    sys.exit(1)
        
        # Compute number of byte rows
        num_byte_rows = (height + 7) // 8
        
        # Initialize data array
        data = [0] * (num_byte_rows * width)
        
        # Pack the bits: 0 for black (0,0,0), 1 for white (255,255,255)
        for y in range(height):
            for x in range(width):
                r, g, b, _ = im.getpixel((x, y))
                is_black = (r, g, b) == (0, 0, 0)
                bit = 0 if is_black else 1
                byte_row = y // 8
                byte_index = byte_row * width + x
                bit_pos = 7 - (y % 8)  # MSB at top
                data[byte_index] |= (bit << bit_pos)
        
        # Prepare output file
        base_name = os.path.basename(input_file)[:-4].upper()  # Remove .png and uppercase
        output_file = input_file[:-4] + '.h'
        
        # Format the sprite data
        bytes_list = [f'0x{b:02X}' for b in data]
        
        def format_array(items, per_line=8):
            lines = []
            for i in range(0, len(items), per_line):
                chunk = items[i:i + per_line]
                line = '    ' + ', '.join(chunk)
                if i + per_line < len(items):
                    line += ','
                lines.append(line + ' \\')
            if lines:
                lines[-1] = lines[-1].rstrip(' ,\\')  # Remove trailing comma and backslash if present
            return '\n'.join(lines) if lines else ''
        
        formatted_data = format_array(bytes_list)
        if not formatted_data:
            formatted_data = '    '  # Empty array, but unlikely
        
        with open(output_file, 'w') as f:
            f.write(f'#define {base_name}_WIDTH {width}\n')
            f.write(f'#define {base_name}_HEIGHT {height}\n')
            f.write(f'#define {base_name}_SPRITE {{ \\\n')
            f.write(formatted_data)
            f.write(', \\\n}\n')
        
        # Print the number of bytes
        print(len(data))
    
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()