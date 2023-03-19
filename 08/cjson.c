
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <Python.h>


void removeChar(char * str, int is_str){
    int i, j;
    int len = strlen(str);
    for(i=0; i < len; i++)
    {
        if(str[i] == ' ' || (is_str != 1 && str[i] == '"'))
        {
            for(j = i; j<len; j++)
            {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

int is_numeric(const char* str)
{
    while (isspace(*str))
       str++;
    
    if (*str == '-' || *str == '+')
       str++;

    while (*str)
    {
        if (!isdigit(*str) && !isspace(*str))
            return 0;
        str++;
    }

    return 1;
}

PyObject* cjson_loads(PyObject* self, PyObject* args)
{
    char *initial_string_arg;
    if(!PyArg_ParseTuple(args, "s", &initial_string_arg))
    {
        printf("ERROR: Failed to parse arguments\n");
        return NULL;
    }
    char *initial_string = strdup(initial_string_arg);
    //printf ("Initial string %s\n", initial_string);
    int len = strlen(initial_string);
    char *str = initial_string + 1; 
    str[strlen(str)-1] = '\0'; 
    char delim[] = ":,";
    char **res  = NULL;
    char *p = strtok (str, delim);
    int counter = 0;
    
    while (p) {
      res = realloc (res, sizeof (char*) * ++counter);
      if (res == NULL)
        exit (-1);
      res[counter - 1] = p;
      p = strtok (NULL, delim);
    }
    
    res = realloc (res, sizeof (char*) * (counter));
    res[counter] = 0;
    
    PyObject *dict = NULL;
    //printf ("Created dict\n");
    if (!(dict = PyDict_New())) {
        printf("ERROR: Failed to create Dict Object\n");
        return NULL;
    }

    PyObject *key = NULL;
    PyObject *value = NULL;
    
    for (int i = 0; i < counter; i+= 2)
    {
        //printf ("Pair number:  %d\n", i);
        //printf ("Key %s\n", res[i]);
        //printf ("Value %s\n", res[i + 1]);
        //printf ("Try to set value\n");
        if (is_numeric(res[i + 1]) == 1)
        {
            //printf("Numeric value");
            removeChar(res[i + 1], 0);
            //printf ("Try to set value\n");
            int num;
            sscanf(res[i + 1], "%d", &num);
            if (!(value = Py_BuildValue("i", num))) {
                printf("ERROR: Failed to build integer value\n");
                return NULL;
            }
        } 
        else
        {
            //printf("String value\n");
            removeChar(res[i + 1], 0);
            if (!(value = Py_BuildValue("s", res[i + 1]))) {
                printf("ERROR: Failed to build integer value\n");
                return NULL;
            }
        }
        removeChar(res[i], 0);
        if (!(key = Py_BuildValue("s", res[i]))) {
            printf("ERROR: Failed to build string value\n");
            return NULL;
        }
        //printf ("Try to set key\n");
        
        //printf ("Try to set Pair\n");
        if (PyDict_SetItem(dict, key, value) < 0) {
            printf("ERROR: Failed to set item\n");
            return NULL;
        }  
    }
    return dict;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char * toArray(int number)
{
    int is_positive = 1;
    int n = log10(abs(number)) + 1;
    if (number < 0)
    {
        n = n+ 1;
        is_positive = 0;
    }
    number = abs(number);
    //printf ("number %d\n", number);
    int i;
    char *numberArray = calloc(n, sizeof(char));
    //printf ("n %d\n", n);
    for (i = n-1; i >= 0; --i, number /= 10)
    {
        //printf ("i %d\n", i);
        //printf ("will be %d\n", ((number % 10) + '0'));
        numberArray[i] = (number % 10) + '0';
    }
    if (is_positive == 0)
    {
        //printf ("0m");
        //printf ("will be %d\n", '-');
        numberArray[0] = '-';
    }
    return numberArray;
}

PyObject* cjson_dumps(PyObject* self, PyObject *args)
{
    PyObject *dict = NULL;
    PyObject *key = NULL, *val = NULL;
    Py_ssize_t pos = 0;

    if (!PyArg_ParseTuple(args, "O", &dict))
    {
        printf("ERROR: Failed to parse arguments of dictionary\n");
        return NULL;
    }
    //printf ("Dict %s\n", dict);
    char* res = "{";
    int counter = 0;
    while (PyDict_Next(dict, &pos, &key, &val)) {
        char* k_ = PyUnicode_AsUTF8(key);
        if (counter != 0)
        {
            k_ = concat(", \"", k_);
        }
        else 
        {
            k_ = concat("\"", k_);
        }
        k_ = concat(k_, "\": ");
        res = concat(res, k_);
        char* v_ = NULL;
        if (PyLong_Check(val) == 0)
        {
            v_ = PyUnicode_AsUTF8(val);
            v_ = concat("\"", v_);
            v_ = concat(v_, "\"");
            res = concat(res, v_);
        }
        else
        {
            //printf ("temp %s\n", v_);
            //printf("Not a string\n");
            int v_tmp = PyLong_AsLong(val);
            v_ = toArray(v_tmp);
            res = concat(res, v_);
        }
       
        
        //printf ("Key %s\n", k_);
        //printf ("Value %s\n", v_);
        counter++;
    }
    res = concat(res, "}");
    //printf ("Res [%s]\n", res);
    
    return Py_BuildValue("s", res);
}


static PyMethodDef methods[] = {
    { "loads", cjson_loads, METH_VARARGS, "Load dict from JSON string"},
    { "dumps", cjson_dumps, METH_VARARGS, "Dict to string"},
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef cjsonmodule = {
    PyModuleDef_HEAD_INIT, "cjson",
    NULL, -1, methods
};

PyMODINIT_FUNC PyInit_cjson(void)
{
    return PyModule_Create( &cjsonmodule);
};