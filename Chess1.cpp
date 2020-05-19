#include <iostream>
#include <windows.h>

using namespace std;

int const n = 8;

 class Chess {
public: int desk[n][n];


public: void Desk_Initializer()
           {
               int sign;
               for (int i = 0; i < n; i++)
               {
                   
                   if (i < 2) sign = 1;
                   else sign = -1;

                   for(int j = 0; j < n; j++)
                   {


                       if ((i == 0) || (i == 7))
                       {
                           
                           if ((j == 0) || (j == 7)) desk[i][j] = 2 * sign; // Ладья Rook
                           if ((j == 1) || (j == 6)) desk[i][j] = 3 * sign; // Конь Knight
                           if ((j == 2) || (j == 5)) desk[i][j] = 4 * sign; // Слон Rook
                           if (j == 3) desk[i][j] = 5 * sign; // Королева Queen
                           if (j == 4) desk[i][j] = 6 * sign; // Король King
                       }
                       if ((i == 1) || (i == 6))
                       {
                           desk[i][j] = 1 * sign; //Пешка Pawn
                       }
                       if ((i > 1) && (i < 6))
                       {
                           desk[i][j] = 0; //Пустое поле
                       }

                   }
               }
              // desk[6][7] = 1;
           }

 public: int Out()
 {
     bool player = true;
     string figure;
     int column_figure;
     int row_figure;
     string point;
     int column_point;
     int row_point;
     while (1) {
         Draw(desk);
         while (1) {
             cout << "Write the column and the row of your figure (c,r)" << endl;
             cin >> figure;                                                       //Выбираем фигуру
             column_figure = (int)figure[1] - 48 - 1;
             row_figure = (int)figure[3] - 48 - 1;
             if ((column_figure > 8) || (row_figure > 8)) continue;
             if (desk[row_figure][column_figure] == 0) continue;
             break;
         }
         while (1) {

             cout << "Write the column and the row of your point (c,r)" << endl;
             cin >> point;                                                       //Выбираем клетку на которую идти (точку)
             column_point = (int)point[1] - 48 - 1;
             row_point = (int)point[3] - 48 - 1;
             if ((column_point > 8) || (row_point > 8)) continue;
             break;
         }
         if (ChessController(column_figure, row_figure, column_point, row_point, player, true)) player = !player;
         else { cout << "Try again" << endl; }
     }
     return 0;
 }

       void Draw(int arr[n][n])
       {
           for (int i = 0; i < n; i++) {
               for (int j = 0; j < n; j++) {
                   if (arr[i][j] >= 0) cout << arr[i][j] << "  ";
                   else cout << arr[i][j] << " ";
               }
               cout << " " << endl;
           }
       }






 public: int ChessController(int figure_column, int figure_row, int point_column, int point_row, bool player, bool flag) //Валидация хода + сам ход
   {

     bool result;
     int sign;
     if (player) sign = 1;
     else sign = -1;

     //cout << "columnF"<< figure_column + 1 << endl;
    // cout << "rowF" << figure_row + 1 << endl;
    // cout << "columnP" << point_column + 1 << endl;
    // cout << "rowP" << point_row + 1 << endl;
    // cout << (abs(desk[figure_row][figure_column])) << endl;
     switch (abs(desk[figure_row][figure_column]))
     {
     case 1: result = Pawn( figure_column,  figure_row,  point_column,  point_row,  player); break;
     case 2: result = Rook(figure_column, figure_row, point_column, point_row, player); break;
     case 3: result = Knight(figure_column, figure_row, point_column, point_row, player); break;
     case 4: result = Bishop(figure_column, figure_row, point_column, point_row, player); break;
     case 5: result = (Bishop(figure_column, figure_row, point_column, point_row, player) + Rook(figure_column, figure_row, point_column, point_row, player)); break;
     case 6: result = King(figure_column, figure_row, point_column, point_row, player); break;
     default: result = false;
     }
     if (result)
     {
         int temp = desk[point_row][point_column];
         desk[point_row][point_column] = desk[figure_row][figure_column]; // Ставим нашу фигуру на выбраное место
         desk[figure_row][figure_column] = 0;  // Сносим нашу фигуру с прежнего места
         if (Check(!player)) {
             if (flag) {
                 if (player) cout << "Check white" << endl;
                 else cout << "Check black" << endl;
             }
             desk[figure_row][figure_column] = desk[point_row][point_column];
             desk[point_row][point_column] = temp;
             if (flag) {
                 if (Mate(player)) {
                     if (player) cout << "Black win" << endl;
                     if (!player) cout << "White win" << endl;
                 }
             }
             return 0;
         }
         if (Check(player)) {
             if (flag) {
                 if (!player) cout << "Check white" << endl;
                 else cout << "Check black" << endl;
                 if (Mate(!player)) {
                     if (player) cout << "Black win" << endl;
                     if (!player) cout << "White win" << endl;
                 }
             }
         }
         if (!flag) {
             desk[figure_row][figure_column] = desk[point_row][point_column];
             desk[point_row][point_column] = temp;
         }

         if ((desk[point_row][point_column] == 1 * sign) && ((point_row == 7) || (point_row == 0)))
         {
             int temp;
             cout << "Enter the value to change ypur figure 1-5" << endl;
             cin >> temp;
             desk[point_row][point_column] = sign * temp;   
         }
         return 1;

     }
     else return 0;
   }



 public: bool Pawn(int figure_column, int figure_row, int point_column, int point_row, bool player) //Пешка
 {
     if((abs(figure_column - point_column)+abs(figure_row - point_row)<=2))
     if (player)
     {
         if ((figure_column == point_column) && (figure_row + 1 == point_row) && (desk[point_row][point_column] == 0)) return true; //Шаг вперед на 0
         if ((figure_column == point_column) && (figure_row + 2 == point_row) && (desk[point_row][point_column] == 0) && (desk[figure_row + 1][figure_column + 1] == 0)) return true; // Шаг вперед на чужую фигуру
         if (((figure_column - 1 == point_column)|| (figure_column + 1 == point_column)) && (figure_row + 1 == point_row) && (desk[point_row][point_column] < 0)) return true; // 2 Шага вперед на первом ходе
     }
     else
     {
         if ((figure_column == point_column) && (figure_row - 1 == point_row) && (desk[point_row][point_column] == 0)) return true; //Шаг вперед на 0
         if ((figure_column == point_column) && (figure_row - 2 == point_row) && (desk[point_row][point_column] == 0) && (desk[figure_row - 1][figure_column - 1] == 0)) return true; // Шаг вперед на чужую фигуру
         if (((figure_column - 1 == point_column ) || (figure_column + 1 == point_column)) && (figure_row - 1 == point_row) && (desk[point_row][point_column] > 0)) return true;// 2 Шага вперед на первом ходе
     }
     return false;
 }


public: bool Rook (int figure_column, int figure_row, int point_column, int point_row, bool player) //Ладья
     {
    if ((figure_column != point_column) && (figure_row != point_row)) return false;  // Если наша точка не стоит ни на одной из линий
    if (player) { if (desk[point_row][ point_column] > 0) return false; } // Если на нашей точке уже стоит наша фигура
    if (!player) { if (desk[point_row][ point_column] < 0) return false; } // Если на нашей точке уже стоит наша фигура
    int selector;
    int column = 0;
    int row = 0;

    if (figure_column > point_column) selector = 1;  // Идём влево 
    if (figure_column < point_column) selector = 2;  // Идём вправо
    if (figure_row > point_row) selector = 3;   // Идём вверх по колонке
    if (figure_row < point_row) selector = 4;  // Идём внизпо колонке

    while (1) // Если попадется хотя бы одна пешка на пути
    {
        switch (selector) {
        case 1: --column; break;
        case 2: ++column; break;
        case 3: --row; break;
        case 4: ++row; break;
        }
        if ((figure_column + column == point_column) && (figure_row + row == point_row)) break;
        if (desk[figure_row + row][figure_column + column] != 0) return false;
    }
    return true;
     }





      public: bool Bishop(int figure_column, int figure_row, int point_column, int point_row, bool player) //Слон
      {
          if ((figure_column == point_column) || (figure_row == point_row)) return false; // Если наша точка не стоит ни на одной из линий
          if (player) { if (desk[point_row][point_column] > 0) return false; } // Если на нашей точке уже стоит наша фигура
          if (!player) { if (desk[point_row][point_column] < 0) return false; } // Если на нашей точке уже стоит наша фигура
          int selector;
          int column = 0;
          int row = 0;

          if ((figure_column > point_column) && (figure_row > point_row)) selector = 1;  // Идём влево вверх
          if ((figure_column < point_column) && (figure_row < point_row)) selector = 2;  // Идём вправо вниз
          if ((figure_row > point_row) && (figure_column < point_column))  selector = 3;   // Идём вверх вправо по колонке
          if ((figure_row < point_row) && (figure_column > point_column)) selector = 4;  // Идём вниз влево по колонке

          while (1) // Если попадется хотя бы одна пешка на пути
          {
              switch (selector) {
              case 1: { --column; --row;  } break;
              case 2: { ++column; ++row; } break;
              case 3: { --row; ++column; } break;
              case 4: { ++row; --column; } break;
              }
              if ((figure_row + row > 7) || (figure_row + row < 0) || (figure_column + column > 7) || (figure_column + column < 0)) return false;
              if ((figure_column + column == point_column) && (figure_row + row == point_row)) break;
              if (desk[figure_row + row][figure_column + column] != 0) return false;
          }
          return true;
      }

            public: bool Knight(int figure_column, int figure_row, int point_column, int point_row, bool player) // Конь
            {
                int sign;
                if (player) sign = 1;
                else sign = -1;
                if ((abs(figure_column - point_column) == 2) && (abs(figure_row - point_row) == 1) && (desk[point_row][point_column] * sign <= 0)) return true; // Ход по модулю 2 по вертикали и 1 по горизонтали
                if ((abs(figure_column - point_column) == 1) && (abs(figure_row - point_row) == 2) && (desk[point_row][point_column] * sign <= 0)) return true; // Ход по модулю 1 по вертикали и 2 по горизонтали
                return false;

            }

            public: bool King(int figure_column, int figure_row, int point_column, int point_row, bool player) // Король
            {
                int sign;
                if (player) sign = 1;
                else sign = -1;
                if (((abs(figure_column - point_column) == 1) || (abs(figure_row - point_row) == 1)) && (desk[point_row][point_column] * sign <= 0)) return true; // Ход на 1 в любую сторону
                return false;
            }



            public: bool Check(bool player)//Шах
            {
                int king_row;
                int king_column;
                int king;
                int sign;
                if (player) sign = 1;
                else sign = -1;
                king = 6 * sign * -1;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (desk[i][j] == king) { king_row = i; king_column = j; break; }
                    }
                }

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (desk[i][j] * sign > 0)
                        {
                            bool result;
 
                            switch (abs(desk[i][j]))
                            {
                            case 1: result = Pawn(j, i, king_column, king_row, player); break;
                            case 2: result = Rook(j, i, king_column, king_row, player); break;
                            case 3: result = Knight(j, i, king_column, king_row, player); break;
                            case 4: result = Bishop(j, i, king_column, king_row, player); break;
                            case 5: result = (Bishop(j, i, king_column, king_row, player) + Rook(j, i, king_column, king_row, player)); break;
                            case 6: result = King(j, i, king_column, king_row, player); break;
                            default: result = false;
                            }
                            if (result) return true;
                        }
                    }
                }
                return false;

            }

            public: bool Mate(bool player) // Мат
              {
                  int sign;
                  if (player) sign = 1;
                  else sign = -1;

                  for (int i = 0; i < n; i++)
                     {
                        for (int j = 0; j < n; j++)
                            {
                                if (desk[i][j] * sign > 0)
                                {
                                    for (int r = 0; r < n; r++)
                                    {
                                        for (int c = 0; c < n; c++)
                                        {
                                            if (desk[r][c] * sign <= 0)
                                            {
                                                if (ChessController(j, i, c, r, player, false)) return false;
                                            }
                                        }
                                    }
                                }
                            }
                     }
                  return true;
              }
};




 int main() {
     Chess Test;
     Test.Desk_Initializer();
     Test.Out();


     return 0;
 }