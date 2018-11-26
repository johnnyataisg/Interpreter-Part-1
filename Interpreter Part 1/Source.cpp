#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "Interpreter.h"
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main(int argc, char* argv[])
{
		VS_MEM_CHECK;

		for (size_t i = 1; i < 11; i++)
		{
			ifstream inputFile(argv[i]);
			ifstream outputFile(argv[i + 10]);
			string line;
			string con;
			//Read all lines from the input file
			while (getline(inputFile, line))
			{
				con = con + line + "\n";
			}

			string line2;
			string con2;
			while (getline(outputFile, line2))
			{
				con2 = con2 + line2 + "\n";
			}
			LexicalAnalyzer lex(con);
			//Generate the list of tokens from the input file
			lex.generateList();
			//Copy the list of tokens into a vector of the parser object
			Parser parser(lex.getList());
			bool run = parser.parse();

			if (run)
			{
				if (i <= 5)
				{
					Interpreter interpreter(parser.getDatalog());
					Database database = interpreter.getDatabase();
					map<string, Relation>::iterator iter = database.begin();
					Relation relation = (*iter).second;
					++iter;
					Relation relation2 = (*iter).second;
					Relation relation3 = relation.join(relation2);
					stringstream ss;
					ss << i;
					cout << "Test " << ss.str() << ": ";
					if (relation3.toString() == con2)
					{
						cout << "Passed" << endl;
					}
				}
				else
				{
					Interpreter interpreter(parser.getDatalog());
					Database database = interpreter.getDatabase();
					map<string, Relation>::iterator iter = database.begin();
					Relation relation = (*iter).second;
					++iter;
					Relation relation2 = (*iter).second;
					Relation relation3 = relation.unionize(relation2);
					stringstream ss;
					ss << i;
					cout << "Test " << ss.str() << ": ";
					if (relation3.toString() == con2)
					{
						cout << "Passed" << endl;
					}
				}
			}
			inputFile.close();
			outputFile.close();
		}
		system("pause");
		return 0;
}