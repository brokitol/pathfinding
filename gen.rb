# generer le tableau
# definire le point de depart

@n = 50
rand = Random.new()

@tab = []
@n.times do |i|
	@tab[i] = []
	@n.times do |j|
		@tab[i][j] = false
	end
end

@graphe = [] # stocker des pairs [p1,p2]
class Point
	attr_reader :y, :x

	@x = 0
	@y = 0

	def initialize(x, y)
		@x = x
		@y = y
	end

	def ==(tmp)
		return true if @x === tmp.x and @y == tmp.y
	end
end

def maj_graphe_and_list(x, y, pos)
	return if x < 0 || x >= @n || y < 0 || y >= @n || @tab[x][y] == true
	p = Point.new(x,y)
	@graphe << [pos,  Point.new(x, y)]
	@lst << p
end

def	choix_direction(x, y)
	@lst = []
	@lst << Point.new(x,y)
	while (@lst.size > 0)
		pos = @lst.pop
		x = pos.x
		y = pos.y
		@tab[x][y] = true
		[:droite, :gauche, :haut, :bas].shuffle!.each do |o|
			if		o == :droite
				maj_graphe_and_list(x - 1, y, pos)
			elsif	o == :gauche
				maj_graphe_and_list(x + 1, y, pos)
			elsif	o == :haut
				maj_graphe_and_list(x, y + 1, pos)
			elsif	o == :bas
				maj_graphe_and_list(x, y - 1, pos)
			#	y += 1
			#	unless x < 0 || x >= @n || y < 0 || y >= @n || @tab[x][y]
			#		@graphe << [pos,  Point.new(x, y)]
			#		@lst << Point.new(x,y)
			#	end
			#	y -= 1
			end
		end
	end
end

puts "debut choix"
choix_direction(0, 0)
puts "fin choix : @n * @n = #{@n * @n} | @graphe = #{@graphe.size}"

# extention du tableau

tab_final = []
@a = @n * 2
@a.times do |x|
	tab_final[x] = []
	@a.times do |y|
		if x % 2 == 0 and y % 2 == 0 # block qui existe deja
			tab_final[x][y] = true
		elsif x % 2 == 1 and y % 2 == 1 # block de coin qui est forcement un mur
			tab_final[x][y] = false
		else
			bool = false
			pt1 = nil
			pt2 = nil
			if x % 2 == 0 # la case represente un passage vertical possible
				pt1 = Point.new x/2, (y - 1)/2
				pt2 = Point.new x/2, (y + 1)/2
			else # la case represente un passage horisontal possible
				pt1 = Point.new (x - 1)/2, y/2
				pt2 = Point.new (x + 1)/2, y/2
			end

			@graphe.each {|g| bool = true if (g[0] == pt1 and g[1] == pt2) or (g[0] == pt2 and g[1] == pt1)}
			tab_final[x][y] = true if bool
		end
		tab_final[x][y] ||= false
	end
end



# affichage du labyrinte
@a.times {|x| print "X"}
puts "X"
tab_final.each do |t|
	print "X"
	t.each {|x| if x then print " " else print "X" end}
	puts ""
end
