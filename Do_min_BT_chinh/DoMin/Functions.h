#pragma once
#include "Header.h"
#include "Console.h"
#include<ctime>
#include<cstdlib>

#define nhapTrai 0x5A
#define nhapPhai 0x58
#define CSWidth 160
#define CSHeight 40

Bang CTBang; // everything about bảng
O** CTO; // cấu trúc ô, một mảng 2 chiều


COORD viTriConTro; // tọa độ con trỏ hiện tại
bool dungPhim = false; // là chưa tác động bàn phím

short Ox; //Tọa độ gốc của bảng
short Oy;

bool playingMode = false;// Chế độ chơi, true: đang chơi
// false: chưa chơi hoặc đã thất bại

short Trang, viTriChon, tongMuc;
// Trang: truy vấn nhằm truy xuất màn hình
// Trang 1: hiển thị dòng màn hình trò chơi mới hoặc thoát
// Trang 2: trò chơi mới, hiển thị 3 cấp độ hoặc quay lại
// Trang 3: với trạng thái đang chơi, thực hiện thao tác(lên, xuống, trái, phải) và cập nhật bảng
// Trang 4: thua cuộc, chuyển playingMode về false, xóa bảng, các chú thích, thực hiện gamemode

short Bang::getDong()
{
	return SoDong; // trả về số dòng của bàn, tương ứng với độ khó
}

short Bang::getCot()
{
	return SoCot; // tương tự với dòng
}

// tạo ma trận bảng, cấp phát từ dòng sang cột
void Bang::taoMaTran()
{
	CTO = new O * [SoDong];
	for (int i = 0; i < SoDong; i++)
	{
		CTO[i] = new O[SoCot];
	}
}

// xóa ma trận bảng, từ cột đến dòng
void Bang::xoaMaTran()
{
	for (int i = 0; i < SoDong; i++)
	{
		delete CTO[i];
	}
	delete CTO;
}

/* tọa độ đặt bảng, công thức tọa độ để điều chỉnh cho bảng
ở giữa màn hình chạy */
void Bang::toaDoBang()
{
	Ox = ((CSWidth / 2) - SoDong);
	Oy = (((CSHeight - 6) - SoCot) / 2) + 7;
}

// khởi tạo bảng
void Bang::khoiTao(short dong, short cot, short soBom)
{
	SoDong = dong;
	SoCot = cot;
	SoBom = soBom; //set up các đối tượng
	BomDaMo = 0;
	SoCo = 0;
	taoMaTran();
	taoBom(); // random các bom cho đến khi đủ số lượng
	toaDoBang();
	viTriConTro = { 0, 0 };  //con trỏ ban đầu ở ô đầu tiên của bảng
	playingMode = true;
	veBang();
	gameMode(1, 0, 0);  // đang chơi
}


// 2 hàm dưới đây thể hiện cách di chuyển con trỏ trong mảng
//Di chuyển theo x: Con trỏ chiếm nửa ô, do đó khi dịch chuyển
//theo x thì nó phải nhân 2 tọa độ trước, cộng Ox là tịnh tiến
short Bang::toaDoX(short x)
{
	return ((x * 2) + Ox);
}

//Di chuyển theo y: vì chỉ cần lướt xuống thì nó xuống
//liên tục không cách, cộng Oy là tịnh tiến
short Bang::toaDoY(short y)
{
	return (y + Oy);
}

void Bang::veO(short x, short y, short kieu)
{
	//Set màu cho ô, quy định ở dưới
	switch (kieu) //kiểu: các trường hợp mà ô có thể có
	{
	case 0: // ô rỗng, màu nền xanh lá
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 10, a);
		break;
		//từ 1 đến 8, là số bom lân cận của ô,sau khi mở ô có nền là màu trắng
	case 1: // kí tự "1" màu xanh dương
		setColorBGTextXY(toaDoX(x), toaDoY(y), 9, 15, a1);
		break;
	case 2: // kí tự "2" màu xanh lá
		setColorBGTextXY(toaDoX(x), toaDoY(y), 2, 15, a2);
		break;
	case 3: // kí tự "3" màu đỏ
		setColorBGTextXY(toaDoX(x), toaDoY(y), 12, 15, a3);
		break;
	case 4: // kí tự "4" màu xanh dương đậm
		setColorBGTextXY(toaDoX(x), toaDoY(y), 1, 15, a4);
		break;
	case 5: // kí tự "5" màu đỏ đậm
		setColorBGTextXY(toaDoX(x), toaDoY(y), 4, 15, a5);
		break;
	case 6: // kí tự "6" màu xanh lơ
		setColorBGTextXY(toaDoX(x), toaDoY(y), 3, 15, a6);
		break;
	case 7:// kí tự "7" màu đen
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 15, a7);
		break;
	case 8:// kí tự "8" màu hồng (khác màu hồng của con trỏ)
		setColorBGTextXY(toaDoX(x), toaDoY(y), 13, 15, a8);
		break;
	case 9:// tương ứng với bom, kí tự là "B", màu nền đỏ, màu chữ đen
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 12, a9);
		break;
	case 10://ô chẵn, tọa độ(x, y) với (x+y)%2=0, màu trắng
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 8, a);
		break;
	case 11://ô lẻ, tọa độ (x,y) với (x+y)%2=1, màu xám
		setColorBGTextXY(toaDoX(x), toaDoY(y), 0, 7, a);
		break;
	case 12://con trỏ, màu hồng
		setColorBGTextXY(toaDoX(x) + 1, toaDoY(y), 0, 13, a0);
		break;
	case 13://cắm cờ, kí hiệu "P", màu chữ đỏ, màu nền vàng
		setColorBGTextXY(toaDoX(x), toaDoY(y), 12, 14, aP);
		break;
	case 14://cắm cờ sai, kí hiệu "Px", màu chữ trắng, màu nền nâu
		setColorBGTextXY(toaDoX(x), toaDoY(y), 15, 6, aPx);
		break;
	case 15://cắm cờ có bom, kí hiệu "B", màu nền vàng nhạt, màu chữ đỏ
		setColorBGTextXY(toaDoX(x), toaDoY(y), 12, 14, aD);
		break;
	}
}

// Mỗi lần thực hiện một thao tác, phải liên tục cập nhật
// sau đó vẽ bảng, vì mỗi lần hiển thị mỗi khác
void Bang::veBang()
{
	for (int i = 0; i < SoDong; i++)
	{
		for (int j = 0; j < SoCot; j++)
		{
			//nếu ô đã cắm cờ, thực hiện vẽ ô theo option 13
			if (CTO[i][j].daCamCo())
			{
				veO(j, i, 13);
			}
			/*số bom lân cận của ô đó > 0, khi đó số bom lân
			cũng sẽ là option để vẽ ô*/
			else if (CTO[i][j].soBomLC() != 0)
			{
				veO(j, i, CTO[i][j].soBomLC());
			}
			//ô đã mở và số ô lân cận là 0, nền xanh, áp option 0
			else if (CTO[i][j].daMo())
			{
				veO(j, i, 0);
			}
			/*2 trường hợp dưới là khi ô chưa mở, vẽ ô theo quy ước bảng
			ô chẵn màu trắng, ô lẻ màu xám*/
			else if ((i + j) % 2 == 0)
			{
				veO(j, i, 10);
			}
			else
			{
				veO(j, i, 11);
			}
			/*dungPhim = true, ghi nhận có thao tác di chuyển,
			cập nhật sự di chuyển của con trỏ, option 12*/
			if (dungPhim)
			{
				veO(viTriConTro.X, viTriConTro.Y, 12);
			}
		}
	}
}

/*Tạo bom random thì miễn là tọa độ bom nằm trong bảng là đủ
Cách thức để random như phương thức dưới đây, cứ rand một vị trí
nếu đã có bom thì rand chỗ khác, cho đến khi đặt đủ số bom ứng
với độ khó*/
void Bang::taoBom()
{
	srand(time(0));
	short soBom = SoBom;
	short i, j;
	while (soBom != 0)
	{
		i = rand() % SoDong;
		j = rand() % SoCot;
		if (CTO[i][j].coBom())
		{
			continue;
		}
		CTO[i][j].setBom(true);
		soBom--;
	}
}

void Bang::clickPhai(short x, short y)//Cam co, tuong ung nut X
{
	if (!CTO[x][y].daMo())
	//tại ô muốn cắm nếu nó không phải là ô rỗng, thì
	{
		/*nếu ô đó đã cắm cờ, bấm X lần nữa để hủy
		khi đó số cờ bớt đi 1, ta cũng đánh dấu lại
		vị trí này thành chưa cắm cờ*/
		if (CTO[x][y].daCamCo())
		{
			CTO[x][y].caiCamCo(false);
			SoCo--;
		}
		/*ngược lại, nếu ô đó chưa cắm cờ, bấm X để đặt cờ
		khi đó số cờ tăng thêm 1, đánh dấu ô đã được cắm*/
		else
		{
			CTO[x][y].caiCamCo(true);
			SoCo++;
		}
	}
	// Cuối cùng ta cập nhật lại bảng
	veBang();
}

short Bang::bomXungQuanh(short x, short y)
{
	short dem(0);/*biến đếm số bom, khởi tạo bằng 0
	Với ô không phải ở biên, nó sẽ có 8 ô lân cận, nhưng
	nếu là ở biên thì sẽ ít hơn, do đó ta dùng 2 vòng for
	kèm theo điều kiện ở biên để tránh trường hợp 
	chỉ số âm để đếm số bom lân cận*/

	/*Điều kiện biên:
	Tọa độ điểm đang xét phải có hoành tung >= 0 và
	và <= số dòng, số cột tương ứng
	*/
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i < 0 || i >= SoDong || j < 0 || j >= SoCot || (i == x && j == y))
			{
				continue;
			}
			if (CTO[i][j].coBom()) dem++;
		}
	}
	return dem;
}

/*
Lật ô, hoặc sẽ dính bom, hoặc không
- Nếu dính bom, chuyển đến kịch bản thất bại
- Nếu không, tăng số ô đã lật lên 1, sau đó lật ô,
số trong ô hiển thị số bom lân cận
  + Nếu số trong ô > 0, cập nhật mỗi ô đó
  + Nếu là 0, lật hết các ô lân cận lên
*/
void Bang::latO(short x, short y)
{
	if (!CTO[x][y].daMo() && !CTO[x][y].daCamCo())
	{
		CTO[x][y].caiMoBom(true);
		if (CTO[x][y].coBom())
		{
			defeat();
		}
		else
		{
			CTBang.BomDaMo++;
			short bomXQ = bomXungQuanh(x, y);
			if (bomXQ > 0)
			{
				CTO[x][y].setBomLC(bomXQ);
			}
			else
			{
				for (int i = x - 1; i <= x + 1; i++)
				{
					for (int j = y - 1; j <= y + 1; j++)
					{
						if (i < 0 || i >= SoDong || j < 0 || j >= SoCot || (i == x && j == y))
						{
							continue;
						}
						latO(i, j);
					}
				}
			}
		}
	}
}


/*
Đưa con trỏ đến tọa độ muốn mở, điều kiện là không phải ô rỗng
và chưa cắm cờ, ta có thể lật ô
*/
void Bang::clickTrai(short x, short y)
{
	if (!CTO[x][y].daMo() && !CTO[x][y].daCamCo())
	{
		latO(x, y);
		//Sau khi lật ô mà playingMode = true thì không dính bom
		//Nếu dính bom, hàm defeat() sẽ cập nhật lại playingMode = false
		if (playingMode)
		{
			//Sau khi mở ô, cập nhật và vẽ lại bảng
			veBang();
			/*
			Hàm check() nhằm kiểm tra liệu người chơi đã win hay chưa
			Điều kiện: số ô đã mở thành công + số bom = số dòng * số cột
			Nếu đúng, chuyển đến victory(), ngụ ý người chơi thắng cuộc
			*/
			if (check())
			{
				victory();
			}
		}
	}
}

/*
- Sau khi thắng cuộc, ta giải phóng bộ nhớ của ma trận
- Trang = 5, tương ứng giao diện chiến thắng,
chuyển đến màn hình đưa người chơi đến 2 lựa chọn, chơi tiếp hoặc dừng lại,
thực hiện ở gameMode(sẽ trình bày ở dưới), in ra kết quả chơi "Thắng"
- deleteRow(4, 1): xóa các dòng ở trên, hàm này ở console.h
*/
void Bang::victory()
{
	playingMode = false;
	xoaMaTran();
	Trang = 5;
	deleteRow(4, 1);
	gameMode(2, 3, 0);
}

/*
- Sau khi thất bại, lật hết các ô có bom, kí hiệu B nền đỏ
- Các ô cắm cờ sai kí hiệu bằng Px
- Các ô cắm cờ đúng kí hiệu bằng B nền vàng
- Sau khi thua cuộc, giải phóng bộ nhớ của ma trận
- Trang = 4, tương ứng giao diện thất bại
chuyển đến màn hình đưa người chơi đến 2 lựa chọn, chơi tiếp hoặc dừng lại,
thực hiện ở gameMode(sẽ trình bày ở dưới), in ra kết quả chơi "Thua"
- deleteRow(4, 1): xóa các dòng ở trên, hàm này ở console.h
*/
void Bang::defeat()
{
	for (int i = 0; i < SoDong; i++)
	{
		for (int j = 0; j < SoCot; j++)
		{
			if (CTO[i][j].daCamCo())
			{
				if (CTO[i][j].coBom())
				{
					veO(j, i, 15);
				}
				else
				{
					veO(j, i, 14);
				}
			}
			else
			{
				if (CTO[i][j].coBom())
				{
					veO(j, i, 9);
				}
			}
		}
	}
	playingMode = false;
	xoaMaTran();
	Trang = 4;
	deleteRow(4, 1);
	gameMode(3, 3, 0);
}

// Hàm check, đã trình bày ở trên
bool Bang::check()
{
	if ((SoBom + BomDaMo) == (SoDong * SoCot))
		return true;
	return false;
}


/*
- Hàm xử lý phím, cấu trúc _KEY_EVENT_RECORD có sẵn dùng để biểu diễn
một input từ bàn phím
- Những đối tượng của _KEY_EVENT_RECORD được sử dụng:

typedef struct _KEY_EVENT_RECORD
{
  BOOL bKeyDown; //nếu key được nhấn, giá trị này là true, ngược lại false
  WORD wVirtualKeyCode;//định vị nút được nhấn
} KEY_EVENT_RECORD;

*/

/*
- Về quy ước của "Trang"
+ Trang = 1: màn hình menu
+ Trang = 2: chọn độ khó
+ Trang = 3: giao diện chơi, khi playingMode = true thì
cứ mỗi lần di chuyển ta cập nhật vị trí con trỏ và vẽ bảng
+ Trường hợp bằng 4 và 5 đã nêu ở trên
*/
void Bang::xuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown) //nếu có nút được nhấn
	{ 
		switch (key.wVirtualKeyCode) //xét các trường hợp nút gõ vào
		{
		case VK_UP://Phim mui ten len
			switch (Trang)
			{
			case 1:
				if (tongMuc == 2)
				{
					/*
					Tổng mục: là số lựa chọn khi đang ở một trang
					Ví dụ: Trang lúc này là 1, có 2 lựa chọn, 0 ứng với
					trò chơi mới, 1 ứng với thoát và dừng chơi
					*/
					if (viTriChon == 0)
					{
						/*vị trí chọn trên 0 sẽ bị out, set lại
						vị trí về 1, ngược lại thì khi nhấn phím lên
						thì vị trí chọn lùi 1 */
						viTriChon = tongMuc - 1;
					}
					else
					{
						viTriChon--;
					}
					//mainMenu để hiển thị giao diện
					CTBang.mainMenu(viTriChon);
				}
				break;
			case 2:
				/*
				Ở trang 2 sẽ có 4 mục, chọn 3 độ khó hoặc quay lại
				*/
				if (tongMuc == 4)
				{
					if (viTriChon == 0)
					{
						viTriChon = tongMuc - 1;
					}
					else
					{
						viTriChon--;
					}
					CTBang.menuLevel(viTriChon);
				}
				break;
			case 3:
				/*
				Khi đang chơi, nhấn nút lên tương ứng với di chuyển
				lên trên, do đó nếu giả sử đang ở ô (x, y), tịnh tiến lên 1 sẽ
				đến ô (x - 1, y - 1), nếu đang ở biên trên và di chuyển lên thì
				đưa nó về lại biên dưới
				*/
				if (playingMode)
				{
					dungPhim = true;
					viTriConTro.Y = ((viTriConTro.Y == 0) ? CTBang.getDong() - 1 : viTriConTro.Y - 1);
					CTBang.veBang();
				}
				break;
			case 4:
				//Trường hợp thua cuộc
				CTBang.gameMode(3, 3, (viTriChon == 0) ? 1 : 0);
				break;
			case 5:
				//Trường hợp thắng cuộc
				CTBang.gameMode(2, 3, (viTriChon == 0) ? 1 : 0);
				break;
			}
			break;
			/*
			Các trường hợp phải, trái, xuống mang ý tưởng tương tự
			phải và trái không cần có case 1, 2 vì 2 trường hợp này
			không cần thao tác trái phải
			*/
		case VK_DOWN://Phim mui ten xuong
			switch (Trang)
			{
			case 1:
				if (tongMuc == 2)
				{
					if (viTriChon == tongMuc - 1)
					{
						viTriChon = 0;
					}
					else
					{
						viTriChon++;
					}
					CTBang.mainMenu(viTriChon);
				}
				break;
			case 2:
				if (tongMuc == 4)
				{
					if (viTriChon == tongMuc - 1)
					{
						viTriChon = 0;
					}
					else
					{
						viTriChon++;
					}
					CTBang.menuLevel(viTriChon);
				}
				break;
			case 3:
				if (playingMode)
				{
					dungPhim = true;
					viTriConTro.Y = ((viTriConTro.Y == CTBang.getDong() - 1) ? 0 : viTriConTro.Y + 1);
					CTBang.veBang();
				}
				break;
			case 4:
				CTBang.gameMode(3, 3, (viTriChon == 0) ? 1 : 0);
				break;
			case 5:
				CTBang.gameMode(2, 3, (viTriChon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_LEFT://Phim mui ten qua trai
			if (playingMode)
			{
				dungPhim = true;
				viTriConTro.X = ((viTriConTro.X == 0) ? CTBang.getCot() - 1 : viTriConTro.X - 1);
				CTBang.veBang();
			}
			break;
		case VK_RIGHT://Phim mui ten qua phai
			if (playingMode)
			{
				dungPhim = true;
				viTriConTro.X = ((viTriConTro.X == CTBang.getCot() - 1) ? 0 : viTriConTro.X + 1);
				CTBang.veBang();
			}
			break;
		case VK_RETURN://Phim Enter
			switch (Trang)
			{
			case 1:
				/*
				Vị trí chọn = 0, ứng với trò chơi mới
				nên khi bấm Enter sẽ nhảy sang trang 2
				*/
				if (viTriChon == 0)
				{
					Trang = 2;
					deleteRow(4, 20);
					//xóa những option hiển thị ở trang 1
					CTBang.menuLevel(0);
				}
				//ngược lại là thoát, dừng chơi
				else
				{
					setBackgroundColor(0);
					Lastpage();
				}
				break;
			case 2:
				/*
				Trang 2:
				+ Vị trí chọn = 0, 1, 2 tương ứng độ khó dễ, trung
				bình, khó, nhảy sang trang 3, trước khi nhảy cần
				xóa một vài lựa chọn hiển thị ở trang 2
				+ = 4 là quay lại trang 1
				*/
				if (viTriChon == 0)
				{
					Trang = 3;
					deleteRow(4, 10);
					CTBang.khoiTao(9, 9, 10);
				}
				else if (viTriChon == 1)
				{
					Trang = 3;
					deleteRow(4, 10);
					CTBang.khoiTao(16, 16, 40);
				}
				else if (viTriChon == 2)
				{
					Trang = 3;
					deleteRow(4, 10);
					CTBang.khoiTao(24, 24, 99);
				}
				else if (viTriChon == 3)
				{
					Trang = 1;
					deleteRow(4, 10);
					CTBang.mainMenu(0);
				}
				break;
			case 4:
			case 5:
				/*
			Trang 4 và 5 chọn chơi tiếp hoặc dừng lại, chơi tiếp
			thì quay lại trang 2, ngược lại dừng chơi
			*/
				if (viTriChon == 0)
				{
					Trang = 2;
					deleteRow(3, CSHeight - 3);
					CTBang.menuLevel(0);
				}
				else
				{
					Lastpage();
				}
				break;
			}
			break;
		case VK_ESCAPE://phím ESC, quay lại trang trước
			switch (Trang)
			{
			case 1: //ở trang 1, chọn ESC xem như dừng chơi
				Lastpage();
				break;
			case 2: //lùi về trang 1
				Trang = 1;
				deleteRow(4, 10);
				CTBang.mainMenu(0);
				break;
				//không có case 3 vì không thể đang chơi thì dừng
			case 4:
			case 5:
				/*Thắng hoặc thua, nhấn ESC để quay lại chọn độ khó để chơi*/
				Trang = 2;
				deleteRow(3, CSHeight - 3);
				CTBang.menuLevel(0);
				break;
			}
			break;
		case nhapTrai://Phím Z, để mở ô
			CTBang.clickTrai(viTriConTro.Y, viTriConTro.X);
			break;
		case nhapPhai://Phim X - cắm cờ vào ô
			CTBang.clickPhai(viTriConTro.Y, viTriConTro.X);
			break;
		}
	}
}

void Bang::xuLy()
{
	while (true)
	{
		DWORD suKien = 0;//Lưu lại sự kiện hiện tại
		DWORD suKienDuocLoc = 0;//Lưu lại số sự kiện đã được lọc
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);//Input đầu vào
		GetNumberOfConsoleInputEvents(HConsoleInput, &suKien);
		//Đặt sự kiện đầu vào của giao diện cho biến suKien
		if (suKien != 0)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[suKien];
			ReadConsoleInput(HConsoleInput, IREventBuffer, suKien, &suKienDuocLoc);
			//Đặt các sự kiện được lưu trữ vào EventBuffer
			//Vòng lặp để đọc sự kiện
			for (DWORD i = 0; i < suKien; i++)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT)
					//Sự kiện dùng bàn phím
				{
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
			}
		}
	}
}

/*Hiển thị những thứ "cần hiển thị" :)) và không thay đổi*/
void Bang::designTittle()
{
	char name[12] = "GAME DO MIN";
	for (int i = 0; i < CSWidth; i++)
	{
		std::cout << "-";
	}
	setColorBGTextXY((CSWidth / 2) - 6, 1, 62, 10, name);
	std::cout << "\n";
	setBackgroundColor(0);
	for (int i = 0; i < CSWidth; i++)
	{
		std::cout << "-";
	}
}

/*
gameMode: đang chơi, thắng hoặc thua
*/
void Bang::gameMode(short stt, short mode1, short x)
{
	viTriChon = x;
	tongMuc = 2;
	char map[20] = "KICH THUOC: %d x %d";
	char bom[11] = "SO BOM: %d";
	char mode[15] = "TRANG THAI: %s";
	setColorBGTextXY(1, 3, 62, 0, map, SoDong, SoCot);
	setColorBGTextXY(1, 4, 62, 0, bom, SoBom);

	if (mode1 == 3)
	{
		char again[13] = "  CHOI LAI  ";
		setColorBGTextXY((CSWidth / 2) - (13 / 2) - 1, 3, 62, ((x == 0) ? 10 : 0), again);
		char esc[10] = "  THOAT  ";
		setColorBGTextXY((CSWidth / 2) - (10 / 2) - 1, 4, 62, ((x == 1) ? 10 : 0), esc);
	}

	if (stt == 1)
	{
		setColorBGTextXY(CSWidth - 22, 4, 62, 0, mode, "DANG CHOI");
	}
	if (stt == 2)
	{
		setColorBGTextXY(CSWidth - 22, 4, 62, 0, mode, "THANG");
	}
	if (stt == 3)
	{
		setColorBGTextXY(CSWidth - 22, 4, 62, 0, mode, "THUA");
	}
	std::cout << "\n";
	setColor(7);
	for (int i = 0; i < CSWidth; i++)
	{
		std::cout << "-";
	}
}

//Giao diện trang 1
void Bang::mainMenu(short x)
{
	viTriChon = x;
	tongMuc = 2;
	char game0[17] = "  TRO CHOI MOI  ";
	setColorBGTextXY((CSWidth / 2) - (17 / 2), 7, 62, ((x == 0) ? 10 : 0), game0);
	char game1[10] = "  THOAT  ";
	setColorBGTextXY((CSWidth / 2) - (10 / 2), 8, 62, ((x == 1) ? 10 : 0), game1);
	char htu1[36] = "HUONG DAN DUNG CONSOLE VA CHOI GAME";
	setColorBGTextXY((CSWidth / 2) - (36 / 2), 12, 62, 0, htu1);
	char htu2[60] = "SU DUNG CAC PHIM MUI TEN LEN XUONG DE DI CHUYEN VI TRI CHON";
	setColorBGTextXY((CSWidth / 2) - (60 / 2), 13, 62, 0, htu2);
	char htu3[66] = "NUT ENTER DE CHON 1 MUC, NUT ESC DE THOAT HOAC TRO VE TRANG TRUOC";
	setColorBGTextXY((CSWidth / 2) - (66 / 2), 14, 62, 0, htu3);
	char htu4[91] = "LUC VAO CHOI: NUT Z DE MO 1 O, NUT X DE CAM CO VAO 1 O (LUU Y: AN X LAN NUA DE HUY CAM CO)";
	setColorBGTextXY((CSWidth / 2) - (91 / 2), 15, 62, 0, htu4);
}

//Giao diện trang 2
void Bang::menuLevel(short x)
{
	viTriChon = x;
	tongMuc = 4;
	char choose[16] = "  CHON DO KHO  ";
	char lv1[23] = "  DE (9x9 VA 10 BOM)  ";
	char lv2[33] = "  TRUNG BINH (16x16 VA 40 BOM)  ";
	char lv3[26] = "  KHO (24x24 VA 99 BOM)  ";
	char back[13] = "  QUAY LAI  ";
	setColorBGTextXY((CSWidth / 2) - (16 / 2), 4, 62, 10, choose);
	setColorBGTextXY((CSWidth / 2) - (23 / 2), 7, 62, ((x == 0) ? 10 : 0), lv1);
	setColorBGTextXY((CSWidth / 2) - (33 / 2), 8, 62, ((x == 1) ? 10 : 0), lv2);
	setColorBGTextXY((CSWidth / 2) - (26 / 2), 9, 62, ((x == 2) ? 10 : 0), lv3);
	setColorBGTextXY((CSWidth / 2) - (13 / 2), 10, 62, ((x == 3) ? 10 : 0), back);
}

//Trang kết thúc chương trình
void Bang::Lastpage()
{
	system("cls");
	setColorBGTextXY_1((CSWidth / 2) - (30 / 2), 9, 62, 0, "XIN CHAO VA HEN GAP LAI");
	gotoXY((CSWidth / 2) - (30 / 2), 12);
	system("pause");
	system("cls");
	exit(0);
}