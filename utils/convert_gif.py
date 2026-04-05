# a python script to convert .gif sprites into
# .h files usable by tiny_graphics
# vibe coded because i dont like python :p
import sys
import os
from PIL import Image

def pack_frame(im, width, height):
    """Pack a single RGBA image into the byte-per-8-rows format."""
    num_byte_rows = (height + 7) // 8
    data = [0] * (num_byte_rows * width)

    for y in range(height):
        for x in range(width):
            r, g, b, a = im.getpixel((x, y))
            if a != 255:
                raise ValueError("Image contains transparent pixels, which is not allowed.")
            if not ((r, g, b) == (0, 0, 0) or (r, g, b) == (255, 255, 255)):
                raise ValueError("Image is not strictly black and white.")
            bit = 0 if (r, g, b) == (0, 0, 0) else 1
            byte_row = y // 8
            byte_index = byte_row * width + x
            bit_pos = 7 - (y % 8)  # MSB at top
            data[byte_index] |= (bit << bit_pos)

    return data

def format_array(items, per_line=8):
    lines = []
    for i in range(0, len(items), per_line):
        chunk = items[i:i + per_line]
        line = '    ' + ', '.join(chunk)
        if i + per_line < len(items):
            line += ','
        lines.append(line + ' \\')
    if lines:
        lines[-1] = lines[-1].rstrip(' ,\\')
    return '\n'.join(lines) if lines else '    '

def main():
    if len(sys.argv) != 2:
        print("Usage: python gif_to_h.py input.gif")
        sys.exit(1)

    input_file = sys.argv[1]
    if not input_file.lower().endswith('.gif'):
        print("Input file must be a .gif file.")
        sys.exit(1)

    try:
        gif = Image.open(input_file)

        # Collect all frames
        frames = []
        try:
            while True:
                frame = gif.convert('RGBA')
                frames.append(frame)
                gif.seek(gif.tell() + 1)
        except EOFError:
            pass  # Reached the last frame

        num_frames = len(frames)
        if num_frames == 0:
            print("GIF contains no frames.")
            sys.exit(1)

        # All frames must share the same dimensions
        width, height = frames[0].size
        for i, frame in enumerate(frames[1:], start=1):
            if frame.size != (width, height):
                print(
                    f"Frame {i} size {frame.size} differs from frame 0 size "
                    f"{(width, height)}. All frames must be the same size."
                )
                sys.exit(1)

        # Pack every frame and concatenate
        all_data = []
        for i, frame in enumerate(frames):
            frame_data = pack_frame(frame, width, height)
            all_data.extend(frame_data)

        bytes_per_frame = (height + 7) // 8 * width

        # Prepare output
        base_name = os.path.basename(input_file)[:-4].upper()  # Remove .gif and uppercase
        output_file = input_file[:-4] + '.h'

        bytes_list = [f'0x{b:02X}' for b in all_data]
        formatted_data = format_array(bytes_list)

        with open(output_file, 'w') as f:
            f.write(f'#define {base_name}_WIDTH {width}\n')
            f.write(f'#define {base_name}_HEIGHT {height}\n')
            f.write(f'#define {base_name}_FRAMES {num_frames}\n')
            f.write(f'#define {base_name}_SPRITE {{ \\\n')
            f.write(formatted_data)
            f.write(', \\\n}\n')

        print(len(all_data))

    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
