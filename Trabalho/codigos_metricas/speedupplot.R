library(extrafont)
library(ggplot2)

df_1 <- data.frame(TipoSpeedUp = rep(c("Teorico", "Pratico"), each = 6) ,Processadores = c(1,2,3,4,5,6),SpeedUp= c(0,3,6,9,12,15,0,2,4,6,7,9))

ggplot(data=df_1, aes(x=Processadores,y=SpeedUp, group = TipoSpeedUp)) +
  geom_line(aes(linetype =TipoSpeedUp, color = TipoSpeedUp, size = TipoSpeedUp))+
  geom_point(shape = 18, size = 3,alpha=0.8) +
  scale_shape_identity()+
  scale_linetype_manual(values = c("dashed", "dashed"))+
  scale_color_manual(values=c('#6059FF', '#FF4B32'))+
  scale_y_continuous(breaks = c(0,3,6,9,12,15))+
  scale_x_discrete(limits=c("1","2","3","4","5","6"))+
  scale_size_manual(values=c(1.5,1.5))+
  theme(legend.position = "top")+
  ggtitle("Comparativo entre os Speed Up's")+
  theme(plot.title = element_text(size=15,face = "bold",vjust = 0.8,lineheight = 0.5,hjust = 0.5)) +
  theme(axis.text.x = element_text(angle=50,size = 12 ,vjust=0.5))+
  theme(axis.text.y = element_text(size = 12 ,vjust=0.5)) +
  theme()+
  labs(x="Numero de Processadores", y= "Speed Up")
