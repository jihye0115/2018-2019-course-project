library(tidyverse)
getwd()
setwd("C:/Temp")

acc<- read_csv("Acc.csv",col_types= cols(.default = col_character()))
veh<- read_csv("Veh.csv",col_types= cols(.default = col_character()))
cas<- read_csv("Cas.csv",col_types= cols(.default = col_character()))
acc<-acc%>%
  select(Accident_Index,Accident_Severity,Number_of_Vehicles,Date,Time, Road_Type,Speed_limit,Light_Conditions, Weather_Conditions, Road_Surface_Conditions, Urban_or_Rural_Area)
cas<-cas%>%
  select(Accident_Index,Casualty_Class,Sex_of_Casualty,Age_of_Casualty,Age_Band_of_Casualty,Casualty_Severity,Casualty_Severity,Car_Passenger, Casualty_Type)
veh<-veh%>%
  select(Accident_Index,Vehicle_Type,Vehicle_Manoeuvre,`Junction_Location`,`1st_Point_of_Impact`,
         `Was_Vehicle_Left_Hand_Drive?`,Sex_of_Driver,Age_of_Driver,`Engine_Capacity_(CC)`,Age_of_Vehicle)
acc<-type_convert(acc)
veh<-type_convert(veh)
cas<-type_convert(cas)
acc_cas <- acc %>% left_join(cas, by="Accident_Index")
acc_veh <- acc %>% left_join(veh, by= "Accident_Index")
acc
veh
cas
print(acc,n=5,width=Inf)
print(veh,n=5,width=Inf)
print(cas,n=5,width=Inf)

summary(acc)
table(acc$Accident_Severity)
table(acc$Number_of_Vehicles)
table(acc$Road_Type)
table(acc$Speed_limit)
table(acc$Light_Conditions)
table(acc$Weather_Conditions)
table(acc$Road_Surface_Conditions)
table(acc$Urban_or_Rural_Area)

summary(cas)
table(cas$Casualty_Class)
table(cas$Sex_of_Casualty)
table(cas$Age_Band_of_Casualty)
table(cas$Casualty_Severity)
table(cas$Car_Passenger)
table(cas$Casualty_Type)

summary(veh)
table(veh$Vehicle_Type)
table(veh$Vehicle_Manoeuvre)
table(veh$Junction_Location)
table(veh$`1st_Point_of_Impact`)
table(veh$`Was_Vehicle_Left_Hand_Drive?`)
table(veh$Sex_of_Driver)

#3
veh1<-veh %>% filter(Age_of_Vehicle >= 0)
summary(veh1$Age_of_Vehicle)
veh1 %>% ggplot(aes(Age_of_Vehicle)) + geom_histogram(binwidth = 1)
veh1 %>% filter(Age_of_Vehicle < 20) %>% ggplot(aes(Age_of_Vehicle)) + geom_histogram(binwidth = 1)
acc_veh %>% filter(Age_of_Vehicle >= 0) %>% ggplot(aes(Accident_Severity,Age_of_Vehicle)) + geom_jitter(alpha = 0.2)


#4
acc_veh %>% filter(Vehicle_Type > 0) %>% ggplot(aes(`Engine_Capacity_(CC)`,Accident_Severity,color=Vehicle_Type)) + geom_freqpoly()

#7
table(acc$Number_of_Vehicles)
ggplot(acc,aes(factor(Number_of_Vehicles))) + geom_bar()
Number_of_Vehicles, Accident_Severity
ggplot(acc,aes(Number_of_Vehicles,Accident_Severity)) + geom_jitter()
ggplot(acc,aes(factor(Accident_Severity))) + geom_bar()
acc %>% filter(Number_of_Vehicles <5) %>%ggplot(aes(parse_double(Number_of_Vehicles),color=factor(Accident_Severity))) + geom_freqpoly(aes(y=..density..))
ggplot(acc,aes(parse_double(Number_of_Vehicles),fill=factor(Accident_Severity))) + geom_histogram(aes(y=..density..))
ggplot(acc,aes(Number_of_Vehicles)) + geom_bar()
ggplot(acc,aes(parse_double(Number_of_Vehicles))) + geom_freqpoly()

acc %>% filter(Number_of_Vehicles <5) %>% ggplot(aes(Number_of_Vehicles,fill=factor(Accident_Severity))) + geom_density(alpha=0.5)
