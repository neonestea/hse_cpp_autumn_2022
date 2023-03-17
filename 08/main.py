#! /usr/bin/env python3

import time

import json

import ujson

import cjson

def main():
    json_str = '{"hello": 10, "world": "value"}'
    start_ts = time.time()
    json_doc = json.loads(json_str)
    end_ts = time.time()
    print(f"Time of execution of JSON {end_ts - start_ts:.3} seconds")
    start_ts = time.time()
    ujson_doc = ujson.loads(json_str)
    end_ts = time.time()
    print(f"Time of execution of UJSON {end_ts - start_ts:.3} seconds")
    start_ts = time.time()
    cjson_doc = cjson.loads(json_str)
    end_ts = time.time()
    print(f"Time of execution of CJSON {end_ts - start_ts:.3} seconds")
    print("My result dict", cjson_doc)
    print("Check with dict", json_doc)
    print("Type", type(cjson_doc))
    start_ts = time.time()
    result = ujson.dumps(ujson_doc)
    end_ts = time.time()
    print(f"Time of execution of UJSON to string {end_ts - start_ts:.3} seconds")
    start_ts = time.time()
    result = json.dumps(json_doc)
    end_ts = time.time()
    print(f"Time of execution of JSON to string {end_ts - start_ts:.3} seconds")
    start_ts = time.time()
    result = cjson.dumps(cjson_doc)
    end_ts = time.time()
    print(f"Time of execution of CJSON to string {end_ts - start_ts:.3} seconds")
    
    
    print("My str result", type(result))
    assert json_doc == ujson_doc == cjson_doc
    assert json_str == cjson.dumps(cjson.loads(json_str))

if __name__ == "__main__":
    main()