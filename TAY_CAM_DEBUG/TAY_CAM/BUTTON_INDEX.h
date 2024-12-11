#define adr_22 0x01  // 0000 0001
#define adr_21 0x02  // 0000 0010
#define adr_19 0x04  // 0000 0100
#define adr_18 0x08  // 0000 1000
#define adr_35 0x10  // 0001 0000
#define adr_32 0x20  // 0010 0000
#define adr_25 0x40  // 0100 0000
#define adr_33 0x80  // 1000 0000
#define adr_34 0x100 // 0001 0000 0000
#define adr_23 0x200 // 0010 0000 0000
#define adr_15 0x400 // 0100 0000 0000 (Chưa kết nối)
#define adr_05 0x800 // 1000 0000 0000
#define adr_26 0x1000 // 0001 0000 0000 0000
#define adr_39 0x2000 // 0010 0000 0000 0000
#define adr_36 0x4000 // 0100 0000 0000 0000

// Cho hai joystick ở chế độ đọc digital
#define adr_Y1_up 0x8000    // 1000 0000 0000 0000
#define adr_Y1_down 0x10000 // 0001 0000 0000 0000 0000
#define adr_X1_left 0x20000 // 0010 0000 0000 0000 0000
#define adr_X1_right 0x40000  // 0100 0000 0000 0000 0000

#define adr_Y2_up 0x80000    // 1000 0000 0000 0000 0000
#define adr_Y2_down 0x100000 // 0001 0000 0000 0000 0000 0000
#define adr_X2_left 0x200000 // 0010 0000 0000 0000 0000 0000
#define adr_X2_right 0x400000  // 0100 0000 0000 0000 0000 0000

int analog_255[4] = {0, 0, 0, 0};
bool stt_analog[8] = {0, 0, 0, 0, 0,0, 0, 0}; // xl, yl, xr, yr; 
uint8_t byte_analog[4] = {0, 0, 0, 0};

uint8_t byte_start = '^'; //
uint32_t frame1 = 0; // gửi giá trị của nút bấm
uint32_t frame2 = 0; // gửi giá trị của analog lần lượt 4 byte
uint8_t frame[10] = {0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 2 cái đầu là khóa 4 cái tiếp là nút, 4 cái cuối là analog
uint8_t byte_end = '%'; 

int max_val = 100, min_val = -100; 
int max_offset = 65, min_offset = 0; 
void Process_analog(){
  analog_255[0] = map(Yleft, 0, 4095, -254, 254) ; 
  analog_255[1] = map(Xleft, 0, 4095, -254, 254) ; 
  analog_255[2] = map(Yright, 0, 4095, -254, 254) ; 
  analog_255[3] = map(Xright, 0, 4095, -254, 254) ; 

  frame2 = 0; 
  for(int i = 0; i < 4 ; i++){
    if(analog_255[i] > min_offset && analog_255[i] < max_offset ){
      analog_255[i] = 0; 
    }
    byte_analog[i] = abs(analog_255[i]); 
    frame2  |= byte_analog[i] << (24 - i*8); 
    frame[6+i] = byte_analog[i]; 

    if( analog_255[i] >= max_val){
      stt_analog[i*2] = 1; 
      stt_analog[i*2 +1] = 0; 
    }else if(analog_255[i] <= min_val){
      stt_analog[i*2] = 0; 
      stt_analog[i*2 +1] = 1;
    }else{
      stt_analog[i*2] = 0; 
      stt_analog[i*2 +1] = 0;
    }
  } 

}


void updateButtons() {


  Process_analog();
  frame1 = 0; 
  if (button22) frame1 |= adr_22; 
  if (button21) frame1 |= adr_21;
  if (button19) frame1 |= adr_19;
  if (button18) frame1 |= adr_18;
  if (button35) frame1 |= adr_35;
  if (button32) frame1 |= adr_32;
  if (button25) frame1 |= adr_25;
  if (button33) frame1 |= adr_33;
  if (button34) frame1 |= adr_34;
  if (button23) frame1 |= adr_23;

  if (stt_analog[0]) frame1 |= adr_Y1_up;
  if (stt_analog[1]) frame1 |= adr_Y1_down;
  if (stt_analog[2]) frame1 |= adr_X1_right;
  if (stt_analog[3]) frame1 |= adr_X1_left;
  if (stt_analog[4]) frame1 |= adr_Y2_up;
  if (stt_analog[5]) frame1 |= adr_Y2_down;
  if (stt_analog[6]) frame1 |= adr_X2_right;
  if (stt_analog[7]) frame1 |= adr_X2_left;

  for(int i = 0; i < 4; i++){
    frame[2 + i] = (frame1 >> ((3-i)*8)) & 0xff; 
  } 
  // if (button15) frame1 |= adr_15;
  // if (button05) frame1 |= adr_05;
  // if (button26) frame1 |= adr_26;
  // if (button39) frame1 |= adr_39;
  // if (button36) frame1 |= adr_36;
}


