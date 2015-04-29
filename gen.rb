# generer le tableau

require_relative "gen.class"


@n = ARGV.first.to_i
@n ||= 10

@dir = ARGV[1]

rand = Random.new()

unless @dir 
	@tab = []
	@graphe = []
	@tab_final = []

	@n.times do |i|
		@tab[i] = []
		@n.times do |j|
			@tab[i][j] = false
		end
	end

	choix_direction(0, 0)
	extention_maze()

	# affichage du labyrinte
	@a.times {|x| print "X"}
	puts "X"
	@tab_final.each do |t|
		print "X"
		t.each {|x| if x then print " " else print "X" end}
		puts ""
	end
	exit
end

@lvl = ARGV[2].to_i
@lvl ||= 2

a = NIL
b = NIL
@lvl.times do |niveau|
	@tab = []
	@graphe = []
	@tab_final = []

	@n.times do |i|
		@tab[i] = []
		@n.times do |j|
			@tab[i][j] = false
		end
	end

	choix_direction(0, 0)
	extention_maze()

	# ajouter un escaliers au meme endrois que l'etage precedant
	if a and b
		@tab_final[a][b] = :E
		a = NIL
		b = NIL
	end

	# ajouter un nouveaux escaliers random si il reste un etage apres
	if niveau < @lvl - 1
		a = rand(1...(@n * 2 - 1))
		b = rand(1...(@n * 2 - 1))
		@tab_final[a][b] = :E
	end

	# creer le dossier si requis
	`mkdir -p #{@dir}`

	# ouvir le fichier
	fd = File.open("#{@dir}/lvl_#{niveau}.maze", "w")

	# ecrire dans le fichier

	# affichage du labyrinte
	@a.times {|x| fd << "X"}
	fd << "X\n"
	@tab_final.each do |t|
		fd << "X"
		t.each do |x|
			if x == :E
				fd << "E"
			elsif x == true
				fd << " "
			else
				fd << "X"
			end
		end
		fd << "\n"
	end

	# fermer le fichier
	fd.close
end
