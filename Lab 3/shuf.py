#!/usr/bin/python                                                                                             

import random, sys, string
from optparse import OptionParser

class shuf:

        def __init__(self, args, input_range, count, repeat):
                self.input_range = input_range
                self.count = count
                self.repeat = repeat
                                
                if len(args) == 0 and len(input_range) == 0:
                    self.input_list = sys.stdin.readlines()
                    
                elif len(args) > 0 and args[0] == '-':
                    self.input_list = sys.stdin.readlines()

                elif len(input_range) > 0 and not len(args) == 0:
                    parser = OptionParser()
                    parser.error("extra operands '{0}'".format(args[0]))
    
                elif len(input_range) == 0 and len(args) > 1:
                    parser = OptionParser()
                    parser.error("extra operands '{0}'".format(args[len(args)-1]))

                else:
                    if len(input_range) > 0 and len(args) == 0:
                        if input_range.find('-') < 0:
                            parser = OptionParser()   
                            parser.error("invalid input range: '{0}'".format(self.input_range))
                            
                        m = list(int(x) for x in input_range.split("-"))
                        self.low = m[0]
                        self.high = m[1]
                        
                        if self.low - self.high > 1:
                            parser = OptionParser()
                            parser.error("invalid input range: '{0}'".format(self.input_range))
 
                        elif self.low - self.high == 1 and self.repeat == True:
                            parser = OptionParser()
                            parser.error("no lines to repeat")
                        
                        self.input_list = list(range(self.low, self.high+1))
                        random.shuffle(self.input_list)
                        
                        if count > len(self.input_list) and not self.repeat:
                            self.count = len(self.input_list)                                   
                        
                    else:
                        f = open(args[0], 'r')
                        self.input_list = f.readlines()
                        f.close()
                        
                        if count > len(self.input_list) and not self.repeat:
                            self.count = len(self.input_list)
                        random.shuffle(self.input_list)
                        
        def printing(self):
            if self.repeat == True:                    
                if self.count == sys.maxsize:
                    if len(self.input_range) > 0:
                        while self.repeat:
                            sys.stdout.write(str(random.choice(self.input_list)) + '\n')
                    else:
                        while self.repeat:
                            sys.stdout.write(random.choice(self.input_list))
                else:
                    if len(self.input_range) > 0:
                        for i in range(self.count):
                            sys.stdout.write(str(random.choice(self.input_list)) + '\n')
                    else:
                        for i in range(self.count):
                            sys.stdout.write(random.choice(self.input_list)) 

            else:
                if len(self.input_range) > 0:
                    for i in range(self.count):
                        sys.stdout.write(str(self.input_list[i]) + '\n')
                else:
                    for i in range(self.count):
                        sys.stdout.write(self.input_list[i])
                
                    
def main():
    
        parser = OptionParser()

        parser.add_option("-i", "--input-range", action="store", type=str, dest="input_range",
                            default='', help="treat each number LO through HI as an input line" )

        parser.add_option("-n", "--head-count", action="store", dest="count",
                            default=sys.maxsize, help="output at most COUNT lines")

        parser.add_option("-r", "--repeat", action="store_true", dest="repeat",
                            default=False, help="display this help and exit")

        options, args = parser.parse_args(sys.argv[1:])

        try:
                input_range = str(options.input_range)
                
        except:
                parser.error("invalid input range: '{0}'".format(options.input_range))

        try:
                count = int(options.count)
        except:
                parser.error("invalid line count: '{0}'".format(options.count))

        try:
                repeat = bool(options.repeat)
        except:
                parser.error("invalid option -- '{0}'".format(options.repeat))

        if count < 0:
                parser_error("invalid line count: '{0}'".format(count))
                
        try:
                generator = shuf(args, input_range, count, repeat)
                generator.printing()

        except IOError as e:
                errno = e.errno
                strerror = e.strerror
                parser.error("I/O error({0}): {1}".format(errno, strerror))
                
if __name__ == '__main__':
        main()




