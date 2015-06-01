#include <iostream>
#include <string>
#include <stdlib.h>
#include <bitset>
#include <math.h>

using namespace std;

const string Pieces[7] = {"EMPTY", "PAWN", "ROOK", "BISHOP", "KNIGHT", "KING", "QUEEN"};
const string PieceLetters[7]={"0", "P", "R", "B", "H", "K", "Q"};
			//   1		
enum val { A, B, C, D, E, F, G};


void printChar( char c){
	int x = 1;
	cout << "Char : " << c << endl;
	for(int i=0; i<8; i++){
		cout << (c & 0x01);
		c >>=1;
	}

}
int binToInt(string binary){
	int value = 0;
	for(int i=0; i<8; i++){
		//cout << " Adding " << binary.at(i) << " for a sum of " << value << " and 2^i = " << pow(2,i) << endl;;
		if(binary.at(7-i) == '1'){
			value += pow(2,i);
		}
	}
	return value;
}
string intToBinary(int value){
	string binary = "00000000";
	for(int i=7; i>=0; i--){
		if(value >= pow(2,i)){
			value -= pow(2,i);
			binary.at(7-i) = '1';
		}
	}
	return binary;
}


class Chessboard{
	private:
		char board[32];
		int letterToNum(char c){
			return (int(c)-65);
		}
	public:
		string pieceAt( int squarenum, char squareletter){
			int charnum = (squarenum+1)/2-1;
			int letterval = letterToNum(squareletter);
			//cout << "\n\nCharnum: " << charnum << "    and letterval : " << letterval;
			int index = charnum + 4*letterval;
			//cout << "\n\nIndex at : " << index << endl << endl;
			char n = board[index];
			//printChar(n);
			if(squarenum % 2 == 1){
				//cout<<"\nShitfting"<<endl;
				n=n>>4;
			}
			// cout << "\nPiece to work with : ";
			// printChar(n);
			// printChar(n<<7);
			// cout << "Testing " << ((n) & 1) << endl;
			string color = "White ";
			if(((n) & 1) > 0){
				//cout<<"\nBlack piece \n\n";
				color = "Black ";
			}
			int pieceIndex = ((n>>1)&1)*1 + ((n>>2)&1)*2 + ((n>>3)&1)*3;
			// cout << "\n\n Piece Index : " << pieceIndex << " which is a " << Pieces[pieceIndex] << endl;
			if(pieceIndex > 0){
				cout << "\nAt " << squareletter << squarenum << " is a " << color << " " <<  Pieces[pieceIndex];
			}else{
				cout << "\nAt " << squareletter << squarenum << " is empty";
			}
			//printChar(n);
			return color+Pieces[pieceIndex];
		}
		int returnanint(){
			return 4;
		}
		void printBoard(){
			for(int k =0 ; k < 4; k ++){
				for( int j = 0; j<8; j++){
					
					int index = j+8*k;
					char character = board[index] >> 4;
					for(int i=0; i<2; i++){
						int pieceIndex = ((character>>1)&1)*1 + ((character>>2)&1)*2 + ((character>>3)&1)*3;
						if(pieceIndex > 0){
							string color = "W";
							if(((character) & 1) > 0){
								color = "B";
							}
							cout << color << PieceLetters[pieceIndex] << "  ";
						}else{
							cout << " -  ";
						}
						character = board[index];
					}
					if(j == 3){cout << endl;}
				}
				cout << endl;
			}
			
		}
		int pieceNameToIndex(string pieceName){
			int i;
			for(i=0; i<7; i++){
				cout << " i " << i << endl;
				if( (pieceName.compare(Pieces[i]) == 0)||(pieceName.compare(PieceLetters[i]) == 0) ){
					cout << "Success";
					return i;
				}
			}
		}
		void clearPieceAt(int index, bool secondHalf){
			string value = intToBinary(board[index]);
			for(int i = 0; i < 3; i++){
				value.at(i+4*secondHalf) = '0';
			}
			board[index] = binToInt(value);
		}
		void movePiece(string pieceName, char destinationChar, int destinationInt, string color = "white"){
			int pieceIndex = pieceNameToIndex(pieceName);
			cout << " PieceIndex : " << pieceIndex << endl;;
			int charnum = (destinationInt+1)/2-1;
			int letterval = letterToNum(destinationChar);
			int index = charnum + 4*letterval;

			char n;
			string binary;
			int existingPiece;
			switch(pieceIndex){
				case 1: 
					cout<< "\nWe have a pawn"<< endl;
					n =  board[index];
					binary = intToBinary( board[index]);
					if(destinationInt % 2 == 1){ n=n>>4; }
					existingPiece = ((n>>1)&1)*1 + ((n>>2)&1)*2 + ((n>>3)&1)*3;
					cout << "Destionation has a " << Pieces[existingPiece] << endl;	
					
					break;
				default:
				 	break;
			}
			return;

		}

		Chessboard(){
			for (int i=0; i<32; i++){
				board[i] = 0;
			}
			board[0] = 'B';
			board[3] = '5';
			board[4] = 162;
			board[7] = ';';
			board[8] = 'b';
			board[11] = '7';
			board[12] = 226;
			board[15] = 61;
			board[16] = 194;
			board[19] = 63;
			board[20] = 'b';
			board[23] = '7';
			board[24] = 162;
			board[27] = ';';
			board[28] = 'B';
			board[31] = '5';
		}
	 	~Chessboard(){}

};



int main(int argc, char * argv){
	cout << "Hello chess world\n";
	char a ='a';

	// printChar(a);
	// cout << endl<< endl;

	Chessboard *gameboard = new Chessboard;
	int boardnum = 2;
	char boardletter = 'A';
	// for( int j = 0; j<4; j++){
	// 	for(boardnum = 1; boardnum <= 8; boardnum ++){
	// 		//cout << "Testing with : " << boardletter << boardnum << endl;
	// 		string alpha = gameboard -> pieceAt(boardnum,  boardletter);

	// 	}
	// 	cout << endl;
	// 	boardletter ++;
	// }
	cout << endl << endl;
	gameboard -> printBoard();
	cout << endl;
	gameboard -> movePiece("PAWN", 'A', 4);
	cout << " testing with 10011000 which is " << binToInt("10011000") << endl;
	cout << " testing with 152 which is " << intToBinary(152) << endl;

	delete gameboard;
}





