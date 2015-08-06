#!/usr/bin/ruby

def largest(a)
  largest_start = current_start = largest_end = current_end = largest_so_far = current_so_far = 0
  (0..(a.count - 1)).each do |i|
    current_end = i
    current_so_far = current_so_far + a[i]

    # If negative, time to reset.
    if current_so_far < 0
      current_start = current_end = i + 1
      current_so_far = 0
      next
    end

    if current_so_far > largest_so_far
      largest_start, largest_end, largest_so_far = current_start, current_end, current_so_far
    end
  end
  return largest_start, largest_end, largest_so_far
end

print largest([1]).to_s + "\n"
print largest([1, 2]).to_s + "\n"
print largest([1, -1, 2]).to_s + "\n"
print largest([2, -8, 3, -2, 4, -10]).to_s + "\n"
print largest([2, -8, -3, -2, -4, -10]).to_s + "\n"
print largest([-2, -8, -3, -2, -4, -10]).to_s + "\n"
print largest([-2, 8, -3, -2, 5, -10]).to_s + "\n"
