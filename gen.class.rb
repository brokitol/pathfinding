# generer le tableau
# definire le point de depart

class Point
	attr_reader :y, :x

	@x = 0
	@y = 0

	def initialize(x, y)
		@x = x
		@y = y
	end

	def ==(tmp)
		@x == tmp.x and @y == tmp.y
	end
end

def maj_graphe_and_list(x, y, pos)
	return if x < 0 || x >= @n || y < 0 || y >= @n
   	return if @tab[x][y] == true
	p = Point.new(x,y)
	@graphe << [pos,  Point.new(x, y)]
	@tab[x][y] = true
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
			maj_graphe_and_list(x + 1, y, pos)	if		o == :droite
			maj_graphe_and_list(x - 1, y, pos)	if		o == :gauche
			maj_graphe_and_list(x, y - 1, pos)	if		o == :haut
			maj_graphe_and_list(x, y + 1, pos)	if		o == :bas
		end
	end
end

def extention_maze()
	@a = @n * 2
	@a.times do |x|
		@tab_final[x] = []
		@a.times do |y|
			mx = (x % 2 == 0)
			my = (y % 2 == 0)
			if mx and my # block qui existe deja
				@tab_final[x][y] = true
			elsif !mx and !my # block de coin qui est forcement un mur
				@tab_final[x][y] = false
			else
				pt1 = nil
				pt2 = nil
				if mx # la case represente un passage vertical possible
					pt1 = Point.new x/2, (y - 1)/2
					pt2 = Point.new x/2, (y + 1)/2
				else # la case represente un passage horisontal possible
					pt1 = Point.new (x - 1)/2, y/2
					pt2 = Point.new (x + 1)/2, y/2
				end
    
				@graphe.each do |g|
					if (g[0] == pt1 and g[1] == pt2) or (g[0] == pt2 and g[1] == pt1)
						@tab_final[x][y] = true
						@graphe.delete g
						break
					end
				end
			end
			@tab_final[x][y] ||= false
		end
	end
end
