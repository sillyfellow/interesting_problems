#!/usr/bin/ruby

def largest(a)
  ls = cs = le = ce = lz = cz = 0
  (0..(a.count - 1)).each do |i|
    ce = i
    cz = cz + a[i]

    if cz < 0
      cs = ce = i + 1
      cz = 0
      next
    end

    if cz > lz
      ls, le, lz = cs, ce, cz
    end
  end
  return ls, le, lz
end

print largest([1]).to_s + "\n"
print largest([1, 2]).to_s + "\n"
print largest([1, -1, 2]).to_s + "\n"
print largest([2, -8, 3, -2, 4, -10]).to_s + "\n"
print largest([2, -8, -3, -2, -4, -10]).to_s + "\n"
print largest([-2, -8, -3, -2, -4, -10]).to_s + "\n"
print largest([-2, 8, -3, -2, 5, -10]).to_s + "\n"
