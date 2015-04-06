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
	@x = 0
	@y = 0

	def initialize(x, y)
		@x = x
		@y = y
	end

	def getX
		return @x
	end

	def getY
		return @y
	end

	def ==(tmp)
		return true if @x === tmp.getX and @y == tmp.getY
	end
end

def	choix_direction(x, y)
	return false if x < 0 || x >= @n || y < 0 || y >= @n || @tab[x][y]
	@tab[x][y] = true
	ordre = [ :droite, :gauche, :haut, :bas ]
	ordre.shuffle!
	ordre.each do |o|
		p1 = Point.new(x,y)
		if o == :droite
			if choix_direction(x - 1, y)
				@graphe << [p1,  Point.new(x - 1, y)]
			end
		end
		if o == :gauche
			if choix_direction(x + 1, y)
				@graphe << [p1,  Point.new(x + 1, y)]
			end
		end
		if o == :haut
			if choix_direction(x, y - 1)
				@graphe << [p1,  Point.new(x, y - 1)]
			end
		end
		if o == :bas
			if choix_direction(x, y + 1)
				@graphe << [p1,  Point.new(x, y + 1)]
			end
		end

		choix_direction(x, y - 1) if o == :haut

		choix_direction(x, y + 1) if o == :bas
	end
	return true
end
 
choix_direction(0, 0)

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
