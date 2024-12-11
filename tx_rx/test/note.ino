 // ý tưởng cho việc nâng cao ứng dụng vào robocon 
/* 
  đầu tiên mã hóa các nút
  bao nhiêu nút bấy nhiêu bít thể hiện. ( DỰ TÍNH 4 BYTE )
  2 byte analog  
  1 byte biến không đồng thời 
  1 byte biến yêu cầu 
==>  TỔNG cộng mình sẽ có 8 byte cần truyền đi từ TX. 
Đồng thời trong lúc đó sẽ có Serial debug. 
Trên tay cầm sẽ có một màn hình HMI, màn hình hiển thị được các thông số mà robot gửi về dạng như trên monitor. 
Tên màn hình cho phép truy cập vào các chế độ của tay cầm. 
Trên màn hình cho phép gửi ký tự bất kỳ tới robot thông qua 1 byte không đồng thời. ( khi này byte chế độ phải được chuyển sang chế độ đặc biệt và mỗi lần bấm gưi một ký tự vẫn đồng thời gửi cả 8 byte đi như bình thường )



*/