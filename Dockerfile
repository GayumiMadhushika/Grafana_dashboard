FROM grafana/grafana:11.5.2

USER root

# Copy the Grafana dashboard script
COPY grafana_dashboard.py /grafana_dashboard.py

# Run Grafana normally
CMD ["/run.sh"]
