library(extrafont)
library(ggplot2)


#Criacao dos dataframes de exemplo pro script
df_1 <- data.frame(TipoExecucao = rep(c("Recursivo", "Iterativo", "Paralelo"), each = 5) ,tamanhoAmostra = c(14,15,16,17,18),tempo= c(20,40,60,80,100,12,200,39,40,240,35,10,50,200,70))
#head(df_1)
#df_2 <- data.frame(tamanhoAmostra = c(14,15,16,17,18),tempo= c(35,10,50,200,70))
#(exec)
#Criacao das linhas do plot
ggplot(data=df_1, aes(x=tamanhoAmostra,y=tempo, group = TipoExecucao)) +
  geom_line(aes(linetype =TipoExecucao, color = TipoExecucao, size = TipoExecucao))+
  geom_point(size = 2, alpha = 0.7) +
  scale_linetype_manual(name = "Tipo de Execução", values = c("solid", "solid","solid"))+
  scale_color_manual(name = "Tipo de Execução", values=c('#6059FF', '#FF4B32', "black"))+
  scale_size_manual(name = "Tipo de Execução", values=c(1,1,1))+
  # theme_classic() +
  theme_minimal() +
  theme(legend.position = "top")+
  ggtitle("Comparativo entre execucoes")+
  theme(plot.title = element_text(size=15,face = "bold",vjust = 0.5,lineheight = 0.5,hjust = 0.5),
        axis.text.y = element_text(face = "bold", size = 12 ,vjust=0.5),
        axis.text.x = element_text(face = "bold"),
        axis.title = element_text(face = "bold")) +
  scale_y_continuous(breaks = seq(0, 250 , 10)) +
  labs(x="Tamanho da Amostra", y= "Tempo (ms)")

# veja o plotly
# https://plot.ly/r/

ggsave("plot1.png", device = "png", scale = 2, dpi = 320)


