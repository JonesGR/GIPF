#include "Struct.cpp"

using namespace std;

void GenerateOuterIndexes(Board& gipf_board);
void GenerateInnerIndexes(Board& gipf_board);
void GenerateIndexes(Board& gipf_board);
bool CheckForRows(Board& gipf_board);
void SetGameState(Board& gipf_board);
void PrintGameBoard(Board& gipf_board);
bool LoadGameBoard(Board& gipf_board);
bool IsDeadLocked(Board& gipf_board);
void PrintGameState(Board& gipf_board);
void IsGameOver(Board& gipf_board);
void DeleteRow(Board& gipf_board, int start_x, int start_y, Cord move, char toSave);
bool CaptureChosenRow(Board& gipf_board, char player, const std::string start, const std::string end);
int CountRows(Board& gipf_board);
void CapturePieces(Board& gipf_board, int skipRow);
bool DoMove(Board& gipf_board, const string start, const string end, bool logs);
void GenerateAllPossibleMoves(Board& gipf_board, vector<MoveVect>& possibleMoves);
void GenerateAllMovesBase(Board& gipf_board, vector<Board>& possibleBoards, bool isEXT);
void GenerateAllPositionMoves(Board& gipf_board);
void GenerateAllPositionMovesEXT(Board& gipf_board);
void GenerateAllPositionMovesNUM(Board& gipf_board);
void GenerateAllPositionMovesEXT_NUM(Board& gipf_board);
void WinningSequenceExist();
void SolveGameState();
