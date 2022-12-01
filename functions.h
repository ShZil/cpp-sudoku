std::vector<std::vector<std::vector<int>>> getBoard();
void printBoard(std::vector<std::vector<std::vector<int>>>);
void printVector(std::vector<std::vector<std::vector<int>>>);
std::vector<std::vector<std::vector<int>>> solve1(std::vector<std::vector<std::vector<int>>>);
std::vector<std::vector<std::vector<int>>> restrictRow(std::vector<std::vector<std::vector<int>>>, int, int);
std::vector<std::vector<std::vector<int>>> restrictColumn(std::vector<std::vector<std::vector<int>>>, int, int);
std::vector<std::vector<std::vector<int>>> restrictSquare(std::vector<std::vector<std::vector<int>>>, int, int, int);
int sum(std::vector<std::vector<std::vector<int>>>);
