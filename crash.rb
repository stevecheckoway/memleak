#!/usr/bin/env ruby

$LOAD_PATH.unshift(File.dirname(__FILE__))

require 'memleak'

begin
  MemLeak::allocation_failure
  puts('Memory allocation succeeded')
  puts('Try: ulimit -v 102400')
rescue NoMemoryError
  puts('failed; leaked memory')
end
