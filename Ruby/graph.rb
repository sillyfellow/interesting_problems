require 'set'

class Edge
  attr_reader :source
  attr_reader :sink
  attr_reader :weight

  def initialize(u, v, weight = 1)
    @source = u
    @sink = v
    @weight = weight
  end

  def to_s
    "#{@source} ---(#{@weight})---> #{@sink}"
  end
end

class Graph

  def initialize(name)
    @name     = name
    @adj_list = {}
  end

  def add_edge(e)
    @adj_list[e.source] ||= Set.new
    puts "Already has an edge #{e}" if @adj_list[e.source].include?(e.sink)
    @adj_list[e.source] << [e.sink, e.weight]
  end

  def edges
    @adj_list.map{ |node, neighbours| neighbours.map{ |neighbour| Edge.new(node, neighbour.first, neighbour.last) } }.flatten
  end

  def nodes
    @adj_list.keys
  end

  def neighbours(node)
    return [] unless @adj_list.include?(node)
    @adj_list[node].map{|neighbour| neighbour.first }
  end

  def explore(node, visited)
    return if visited[node] # redundant?
    # pre visit thingy
    print " => #{node}"
    visited[node] = true
    neighbours(node).each do |neighbour|
      explore(neighbour, visited) unless visited[neighbour]
    end
    # post visit thingy
  end

  def dfs
    visited = Hash.new(false)
    nodes.each do |node|
      print "##" unless visited[node]
      explore(node, visited) unless visited[node]
    end
  end

  def bfs
    visited = Hash.new(false)
    queue = []
    nodes.each do |node|
      print "\n##" unless visited[node]
      queue.push(node) unless visited[node]
      while !queue.empty? do
        # pre visit thingy
        current = queue.delete_at(0)
        next if visited[current]
        print " -> #{current}"
        visited[current] = true
        neighbours(current).each do |neighbour|
          queue.push(neighbour) unless visited[neighbour]
        end
        # post visit thingy
      end
    end
  end

  def to_s
    "#{@adj_list.map {|n| n.to_s }.join("\n")}"
  end

end

def rc
  array = ('a'..'z').to_a
  array[rand(array.count)]
end

thattakam_edges = [Edge.new("amba", "bish",  1), Edge.new("amba", "high",  3), Edge.new("amba", "mann",  5),
                   Edge.new("bell", "nadu",  2), Edge.new("bini", "nbus",  2), Edge.new("bini", "stat",  1),
                   Edge.new("bish", "amba",  1), Edge.new("bish", "mukk",  3), Edge.new("bish", "zooo",  1),
                   Edge.new("cldy", "kdk_",  8), Edge.new("cldy", "shak", 30), Edge.new("cldy", "vel_", 13),
                   Edge.new("gvr_", "ijk_", 24), Edge.new("gvr_", "pknm", 25), Edge.new("high", "muni",  1),
                   Edge.new("high", "post",  1), Edge.new("ijk_", "gvr_", 24), Edge.new("ijk_", "kdk_", 11),
                   Edge.new("ijk_", "koka", 20), Edge.new("ijk_", "pkd_", 14), Edge.new("kdk_", "cldy",  8),
                   Edge.new("kdk_", "ijk_", 11), Edge.new("kdk_", "nly_",  4), Edge.new("kdk_", "vel_",  8),
                   Edge.new("koka", "bell",  1), Edge.new("koka", "post",  2), Edge.new("koka", "west",  5),
                   Edge.new("mann", "amba",  5), Edge.new("mann", "cldy", 26), Edge.new("mann", "mukk",  2),
                   Edge.new("mann", "nly_", 15), Edge.new("mukk", "bish",  3), Edge.new("mukk", "mann",  2),
                   Edge.new("muni", "bell",  1), Edge.new("muni", "post",  1), Edge.new("mup_", "vel_",  9),
                   Edge.new("nadu", "bini",  2), Edge.new("nadu", "patt",  2), Edge.new("nadu", "west",  3),
                   Edge.new("nbus", "bini",  2), Edge.new("nbus", "zooo",  3), Edge.new("nly_", "ijk_", 13),
                   Edge.new("nly_", "kdk_",  4), Edge.new("nly_", "pkd_",  4), Edge.new("nly_", "shak", 18),
                   Edge.new("patt", "nbus",  2), Edge.new("patt", "pknm",  2), Edge.new("patt", "shor", 22),
                   Edge.new("pkd_", "mup_",  9), Edge.new("pkd_", "nly_",  3), Edge.new("pkd_", "shak", 14),
                   Edge.new("pknm", "gvr_", 30), Edge.new("pknm", "patt",  2), Edge.new("plkd", "mann", 60),
                   Edge.new("plkd", "shor", 40), Edge.new("post", "high",  1), Edge.new("post", "koka",  2),
                   Edge.new("post", "muni",  1), Edge.new("post", "shak",  2), Edge.new("shak", "cldy", 30),
                   Edge.new("shak", "koka",  2), Edge.new("shor", "gvr_", 31), Edge.new("shor", "nbus", 22),
                   Edge.new("shor", "plkd", 40), Edge.new("stat", "amba",  4), Edge.new("stat", "bish",  3),
                   Edge.new("stat", "high",  1), Edge.new("stat", "zooo",  2), Edge.new("vel_", "cldy", 13),
                   Edge.new("west", "koka",  5), Edge.new("west", "nadu",  3), Edge.new("west", "pknm",  3),
                   Edge.new("zooo", "nbus",  3), Edge.new("zooo", "stat",  2), ]

g = Graph.new('thattakam')
#90.times { g.add_edge(Edge.new(rc, rc, 1 + rand(20))) }
#puts g.nodes
#puts g.edges
thattakam_edges.shuffle.each { |e| g.add_edge(e) }
puts g

g.dfs
g.bfs

#puts e

