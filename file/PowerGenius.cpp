#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"

int getPowerMode();
void changeRefreshRate(int mode);
int indexOf(const char* text, const char* pattern, const int start);

int main() {
	//切换电源方案
	system(COMMAND_1);
	//获取电源模式
	int mode = -1;
	for (int i = 0; i < MAX_RETRY; i++) {
		mode = getPowerMode();
		if (mode != -1) {
			break;
		}
	}
	if (mode == -1) return 0;
	changeRefreshRate(mode);
	return 0;
}

//判断电脑AC/Battery供电 -1 Unknow | 0 AC | 1 Battery
int getPowerMode() {
	system(COMMAND_2);
	//打开文件
	FILE* filep;
	fopen_s(&filep, REPORT_PATH, "r");
	if (filep == NULL) {
		return -1;
	}
	char buffer[BUFFER_SIZE];
	int start;
	//解析报告
	while (fread(buffer, sizeof(char), sizeof(buffer), filep)) {
		if ((start = indexOf(buffer, KEYWORD, 0)) > 0) {
			fclose(filep);
			if (indexOf(buffer, AC, start) > 0) {
				return 0;
			}
			else if (indexOf(buffer, BATTERY, start) > 0) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
	return -1;
}

//切换屏幕刷新率
void changeRefreshRate(int mode) {
	//判断当前是否为高刷新率
	bool isEnabled = false;
	FILE* sign;
	fopen_s(&sign, SIGN_PATH, "r");
	if (sign != NULL) {
		isEnabled = true;
		fclose(sign);
	}
	//判断模式
	if (mode == 0) {
		if (!isEnabled) {
			FILE* newSign;
			fopen_s(&newSign, SIGN_PATH, "w");
			if (newSign != NULL) {
				char content[] = "1";
				fwrite(content, sizeof(char), sizeof(content), newSign);
				fclose(newSign);
			}
			system(HIGH_RATE);
		}
	}
	else {
		if (isEnabled) {
			remove(SIGN_PATH);
			system(LOW_RATE);
		}
	}
}

int indexOf(const char* text, const char* pattern, const int start) {
	int i = 0, j = -1;
	int tLen = strlen(text), pLen = strlen(pattern);
	int* next = (int*)malloc(sizeof(int) * pLen);
	
	//计算next数组
	next[0] = -1;
	while (i < pLen - 1) {
		if (j == -1 || pattern[i] == pattern[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
	
	//匹配
	i = start;
	j = 0;
	while (i < tLen && j < pLen) {
		if (j == -1 || text[i] == pattern[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	
	free(next);
	return j == pLen ? i - j : -1;
}
