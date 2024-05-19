puts "Hello, World!"

puts 'hexlet'.methods.grep(/\?/)


def average(from, to)
  sum = 0
  count = 0
  loop do
    break if from == to
    from += 1
    sum += from
    count += 1
  end
  (sum.to_f / count.to_f)
end

def average(from, to)
  sum = 0
  to = to+1
  count = to - from
  current = from
  while (current < to)
    sum += current
    current += 1
  end
  (sum.to_f / count.to_f)
end
