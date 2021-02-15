// Width and height of the bitmap
unsigned size_x = 1280, size_y = 720;
// Rows top-down,
// for each row pixels from left to right,
// for each pixel components B, G, R = 0..255.
unsigned data_size = size_x * size_y * 3;
unsigned char *data = new unsigned char[data_size];

// Here fill the data, for example:
for (unsigned y = 0, i = 0; y < size_y; ++y) {
  for (unsigned x = 0; x < size_x; ++x) {
    data[i++] = 255; // G
    data[i++] = 255; // B
    data[i++] = 255; // R
  }
}

// Prepare data structures
DWORD data_offset = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
DWORD file_size = data_offset + data_size;
BITMAPFILEHEADER file_header = {
  0x4D42, // bfType = "BM"
  file_size, // bfSize
  0, 0, // bfReserved1, bfReserved2
  data_offset, // bfOffBits
};
BITMAPINFOHEADER info_header = {
  sizeof(BITMAPINFOHEADER), // biSize
  (LONG)size_x, -(LONG)size_y, // biWidth, biHeight
  1, // biPlanes
  24, // biBitCount
  BI_RGB, // biCompression
  0, // biSizeImage
  72, 72, // biXPelsPerMeter, biYPelsPerMeter
  0, 0, // biClrUsed, biClrImportant
};

// Save file
FILE *file = fopen("file_name.bmp", "wb");
fwrite(&file_header, sizeof(file_header), 1, file);
fwrite(&info_header, sizeof(info_header), 1, file);
fwrite(&data[0], 1, data_size, file);
fclose(file);

// Finalize
delete [] data;