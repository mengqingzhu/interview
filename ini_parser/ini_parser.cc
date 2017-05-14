#include "ini_parser.h"
#include <stdio.h>


namespace qh
{
	INIParser::INIParser(){
	}

	INIParser::~INIParser(){
		default_map.clear();
		text_map.clear();
	}

	bool INIParser::Parse(const std::string& ini_file_path){
		FILE *fp;
		fp = fopen(ini_file_path.c_str(), "r");
		if(fp == NULL) return false;
		std::map<std::string, std::string> cur_map;
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		std::string map_key;
		while((read = getline(&line, &len, fp)) != -1){
			if(len == 0) continue;
			char * pCurrent = line;
			char * pEnd = line + read - 1;
			while(pCurrent < pEnd && *pCurrent == ' ') ++pCurrent;
			while(pEnd > pCurrent && *(pEnd - 1) == ' ') --pEnd;
			if(pCurrent == pEnd) continue;
			if(*pCurrent == '['){
				++pCurrent;
				char * pTemp = pCurrent;
				while(pTemp < pEnd && *pTemp != ']') ++pTemp;
				if(pTemp == pEnd) continue;
				std::string map_key_t(pCurrent, pTemp - pCurrent);
				if(text_map.find(map_key_t) == text_map.end()){
					if(cur_map.empty())
						map_key = map_key_t;
					else{
						text_map[map_key] = cur_map;
						cur_map.clear();
						map_key = map_key_t;
					}
				}else{
					return false;
				}
			}else{
				const char * pSeperator = GetLocation(pCurrent, pEnd, "=");
				if(pSeperator == NULL) continue;
				if(pSeperator == pCurrent) continue;
				std::string key(pCurrent, pSeperator - pCurrent);
				std::string value(pSeperator + 1, pEnd - pSeperator - 1);
				if(cur_map.find(key) != cur_map.end()) return false;
				cur_map[key] = value;
			}
		}
		text_map[map_key] = cur_map;
		fclose(fp);
		if(line)
			delete line;
		return true;
	}

	bool INIParser::Parse(const char *ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator){
		if(ini_data == NULL) return false;
		if(!default_map.empty()) default_map.clear();
		const char * pCurrent = ini_data;
		const char * pEnd = pCurrent + ini_data_len;
		const char * pTemp;
		int key_seperator_len = line_seperator.size();
		int value_seperator_len = key_value_seperator.size();
		while((pTemp = GetLocation(pCurrent, pEnd, line_seperator)) != NULL){
			const char * pSeperator = GetLocation(pCurrent, pTemp, key_value_seperator);
			if(pSeperator != NULL && pCurrent != pSeperator){
				std::string key(pCurrent, pSeperator - pCurrent);
				std::string value(pSeperator + value_seperator_len, pTemp - pSeperator - value_seperator_len);
				if(default_map.find(key) != default_map.end()) return false;
				default_map[key] = value;
			}
			pCurrent = pTemp + key_seperator_len;
		}
		if(pCurrent == pEnd) return true;
		if((pTemp = GetLocation(pCurrent, pEnd, key_value_seperator)) != NULL){
			if(pCurrent != pTemp){
				std::string key(pCurrent, pTemp - pCurrent);
				std::string value(pTemp + value_seperator_len, pEnd - pTemp - value_seperator_len);
				if(default_map.find(key) != default_map.end()) return false;
				default_map[key] = value;
			}
		}
		return true;
	}

	const std::string& INIParser::Get(const std::string& key, bool* found){
		if(default_map.find(key) != default_map.end()){
			if(found != NULL) *found = true;
		}else{
			if(found != NULL) *found = false;
		}
		return default_map[key];
	}

	const std::string& INIParser::Get(const std::string& section, const std::string& key, bool *found){
		std::map<std::string, std::string> tempMap;
		std::map<std::string, std::string> &cur_map = tempMap;
		if(text_map.find(section) == text_map.end()){
			if(found != NULL) *found = false;
			return text_map[section][key];
		}else{
			cur_map = text_map[section];
			if(cur_map.find(key) == cur_map.end()){
				if(found != NULL) *found = false;
			}else{
				if(found != NULL) *found = true;
			}
			return cur_map[key];
		}
	}

	const char * INIParser::GetLocation(const char *pStart, const char * pEnd, const std::string& seperator){
		const char * pCurrent1 = pStart;
		int length = seperator.size();
		const char * pCurrent2;
		while(pCurrent1 < pEnd){
			const char * pCur = pCurrent1;
			pCurrent2 = seperator.c_str();
			while(pCur < pEnd && pCurrent2 != '\0' && *pCur == *pCurrent2){
				++pCur;
				++pCurrent2;
			}
			if(pCur - pCurrent1 == length) return pCurrent1;
			++pCurrent1;
		}
		return NULL;
	}
}
