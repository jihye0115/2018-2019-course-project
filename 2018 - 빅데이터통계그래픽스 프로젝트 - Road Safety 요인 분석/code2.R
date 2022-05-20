library(tidyverse)
getwd()
setwd("C:/Temp")

acc<- read_csv("Acc.csv",col_types= cols(.default = col_character())) %>% select(
  Accident_Index, Accident_Severity, Date, Time, Road_Type, Speed_limit, Light_Conditions, Weather_Conditions, Road_Surface_Conditions, Urban_or_Rural_Area)
type_convert(acc)
veh<- read_csv("Veh.csv",col_types= cols(.default = col_character())) %>% select(
  Accident_Index,Vehicle_Type, Vehicle_Manoeuvre, Junction_Location, 
  `1st_Point_of_Impact`, `Was_Vehicle_Left_Hand_Drive?`, Sex_of_Driver, Age_of_Driver,`Engine_Capacity_(CC)`, Age_of_Vehicle)
type_convert(veh)
cas<- read_csv("Cas.csv",col_types= cols(.default = col_character())) %>% select(Accident_Index,Casualty_Class, Sex_of_Casualty,Age_of_Casualty, Age_Band_of_Casualty,Casualty_Severity,Casualty_Type)
type_convert(cas)
acc
veh
cas

acc_cas <- acc %>% left_join(cas, by="Accident_Index")
acc_veh <- acc %>% left_join(veh, by= "Accident_Index")
acc_cas
acc_veh

#9
cas0<- read_csv("Cas.csv",col_types= cols(.default = col_character()))
type_convert(cas0)
View(cas0)
cas0 %>% filter(Car_Passenger %in% 1:2) %>% ggplot(aes(x=Casualty_Severity,fill=Car_Passenger)) + geom_bar()

#10
View(veh)
veh %>% filter(Sex_of_Driver %in% 1:2) %>% ggplot(aes(Sex_of_Driver, Age_of_Driver)) + geom_jitter(alpha=0.1)
#veh %>% filter(Sex_of_Driver %in% 1:2) %>% ggplot(aes(Sex_of_Driver, Age_of_Driver)) + geom_boxplot()
veh %>% filter(Sex_of_Driver %in% 1:2) %>% ggplot(aes(Age_of_Driver, color=Sex_of_Driver)) + geom_freqpoly()
(veh_t<-veh %>% filter(Sex_of_Driver %in% 1:3, Age_of_Driver != -1) %>% mutate(Age_of_Driver=parse_number(Age_of_Driver)))
table(veh_t$Age_of_Driver)
table(veh_t$Sex_of_Driver)
veh_t%>% ggplot(aes(Age_of_Driver, color=Sex_of_Driver)) + geom_freqpoly()
veh_t%>% ggplot(aes(Age_of_Driver, color=Sex_of_Driver)) + geom_freqpoly(aes(y=..density..),bin=1) #성별차이 거의 없ㅇ

#11
  table(veh$Age_of_Vehicle)
veh %>% filter(Age_of_Vehicle != -1) %>% mutate(Age_of_Vehicle=parse_number(Age_of_Vehicle)) %>% ggplot(aes(Age_of_Vehicle)) + geom_histogram(bin=1)
veh %>% filter(Age_of_Vehicle != -1) %>% mutate(Age_of_Vehicle=parse_number(Age_of_Vehicle)) %>% ggplot(aes(Age_of_Vehicle)) + geom_freqpoly(aes(y=..density..),bin=1)
veh %>% filter(Age_of_Vehicle != -1) %>% mutate(Age_of_Vehicle=parse_number(Age_of_Vehicle)) %>% ggplot(aes(Age_of_Vehicle,color=Vehicle_Type)) + geom_freqpoly()

#12
View(acc)
acc0<- read_csv("Acc.csv",col_types= cols(.default = col_character()))
type_convert(acc0)
table(acc0$Number_of_Vehicles)
acc0 %>% mutate(Number_of_Vehicles=parse_double(Number_of_Vehicles)) %>% ggplot(aes(Accident_Severity,Number_of_Vehicles))+geom_jitter()
acc0 %>% mutate(Number_of_Vehicles=parse_double(Number_of_Vehicles)) %>% ggplot(aes(Number_of_Vehicles,Accident_Severity))+geom_jitter(alpha=0.1)
acc0 %>% mutate(Number_of_Vehicles=parse_double(Number_of_Vehicles)) %>% ggplot(aes(Number_of_Vehicles,color=Accident_Severity)) + geom_freqpoly(aes(y=..density..))
acc0 %>% mutate(Number_of_Vehicles=parse_double(Number_of_Vehicles)) %>% ggplot(aes(Number_of_Vehicles,color=Accident_Severity)) + geom_freqpoly(aes(y=..density..)) + facet_wrap(~Accident_Severity)