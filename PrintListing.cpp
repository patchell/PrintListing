#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

bool PrintFile(const char* pName, FILE* pOut)
{
	FILE* pIn = 0;
	bool rV = true;
	int c;
	static int FormFeed = 12;

	if (fopen_s(&pIn, pName, "r") == 0)
	{
		fprintf(pOut, "\n ---------- %s -------------\n", pName);
		while ((c = fgetc(pIn)) != EOF)
		{
			if (c == '\t')
			{
				int i;

				for (i = 0; i < 4; ++i)
					fputc(' ', pOut);
			}
			else
			{
				fputc(c, pOut);
			}
		}
		fputc(FormFeed, pOut);
		fclose(pIn);
	}
	else
	{
		rV = false;
		fprintf(stderr, "Could not open %s\n", pName);
	}
	return rV;
}

bool search(const char* pFileSpec, FILE* pOut)
{
	intptr_t hFile;
	_finddata_t FileInfo;
	bool Loop = true;
	bool rV = true;

	hFile = _findfirst(pFileSpec, &FileInfo);
	if (hFile > 0)
	{
		while (Loop)
		{
			fprintf(stderr, "%s\n", FileInfo.name);
			if (PrintFile(FileInfo.name, stdout) == false)
				Loop = false;
			else if (_findnext(hFile, &FileInfo) < 0)
				Loop = false;
		}
		_findclose(hFile);
	}
	else
	{
		fprintf(stderr, "No %s Files\n", pFileSpec);
	}
	return rV;
}

int main(int argc, char* argv[])
{
	fprintf(stderr, "Print a Listing\nVer 0.0.1\n");
	search("*.h", stdout);
	search("*.cpp", stdout);
	fprintf( stderr, "Done\n");
	return 0;
}
