/* 
 * File:   StringHelper.h
 * Author: peclevens
 *
 * Created on July 3, 2016, 2:02 PM
 */

#ifndef STRINGHELPER_H
#define STRINGHELPER_H

class StringHelper {
public:
    static char **split(char *text, const char *delimiter);
    static char *trim(char *text);
    static bool isspace(int c);

};


#endif /* STRINGHELPER_H */

