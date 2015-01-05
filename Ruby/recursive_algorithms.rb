
def power_set(s)
  return [[]] if s.empty?
  small_powers = power_set(s[1..-1])
  small_powers + small_powers.map { |sm| sm + [s[0]] }
end

def perm(s)
  return [] if s.empty?
  return [s] if s.size == 1
  permus = perm(s[1..-1])
  permus.map{ |p| (0..(p.size - 1)).map { |i| p[0..i] + s[0] + p[(1+i)..-1] } }.flatten
end

print power_set([1, 2, 3, 4, 5, 6])
print perm('helowr')
