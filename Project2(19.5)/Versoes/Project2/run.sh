for i in {1..6}
do
	./al058 < ./p2_Tstudents/T0$i/input > ./p2_Tstudents/T0$i/myoutput
	diff ./p2_Tstudents/T0$i/output  ./p2_Tstudents/T0$i/myoutput
done
for i in {1..4}
do
	./al058 < testes_enunciado/input$i.txt > testes_enunciado/myoutput
	diff testes_enunciado/myoutput testes_enunciado/output$i.txt
done
for i in {1..4}
do
	./al058 < testst2-students/in$i > testst2-students/myoutput
	diff testst2-students/myoutput testst2-students/out$i
done
